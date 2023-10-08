
#include <desdun_engine/src/app/debug/debug.h>
#include <desdun_engine/src/resources/resource.hpp>

#include <desdun_engine/include/glew/glew.h>
#include <desdun_engine/include/glfw/glfw3.h>

#include "renderer.h"

namespace Desdun
{

	Renderer::Renderer(Shader* shaderDefault)
		: defaultShader(shaderDefault)
	{
		const Color4& c = targetColour;
		glClearColor(c.r, c.g, c.b, c.a);

		queue = new Command[commandQueueSize];

		// quad renderer
		{
			// index buffer setup
			uint* indexBuffer = new uint[maxIndices];


			uint indexOffset = 0;

			for (uint i = 0; i < maxIndices; i += 6)
			{
				indexBuffer[i + 0] = 0 + indexOffset;
				indexBuffer[i + 1] = 1 + indexOffset;
				indexBuffer[i + 2] = 2 + indexOffset;

				indexBuffer[i + 3] = 0 + indexOffset;
				indexBuffer[i + 4] = 2 + indexOffset;
				indexBuffer[i + 5] = 3 + indexOffset;

				indexOffset += 4;
			}

			indexBatch = IndexBuffer::make(indexBuffer, maxIndices);
			delete[] indexBuffer;

			// vertex buffer setup
			vertices = new Vertex[maxVertices];
			verticesHead = vertices;

			batchArray = VertexArray::make();

			vertexBatch = VertexBuffer::make(maxVertices * sizeof(Vertex));
			vertexBatch->SetBufferLayout({
				{ LayoutType::Float, 3 },	// position
				{ LayoutType::Float, 4 },	// tint
				{ LayoutType::Float, 2 },	// texture coordinates
				{ LayoutType::Float, 1 },	// texture layer
				{ LayoutType::Float, 1 }	// texture slot index
				});

			batchArray->PushVertexBuffer(vertexBatch);
			batchArray->SetIndexBuffer(indexBatch);
		}

		// set up texture stuff
		{
			textures = new Ref<TextureArray>[allocatedTextureSlots];

			samplers = new int[allocatedTextureSlots];
			for (int i = 0; i < allocatedTextureSlots; i++)
			{
				samplers[i] = i;
			}
		}

		setShader(defaultShader);
	}
	
	Renderer::~Renderer()
	{
		delete[] textures;
		delete[] queue;
		delete[] vertices;
		delete[] samplers;
	}

	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::enqueue(const Command& rawCommand)
	{
		Command command = { rawCommand };

		if (command.image->textureAlloc == nullptr)
		{
			auto it = std::find_if(textureIndex.begin(), textureIndex.end(), 
				[&](Ref<TextureArray> array) 
				{ 
					return array->GetBaseSize() == command.image->getSize(); 
				}
			);

			if (it == textureIndex.end())
			{
				auto texture = CreateRef<TextureArray>(command.image->size, maxTextureArrayDepth);
				command.image->allocate(texture);

				dd_log_fh("allocated texture {}*{}*{}", "Renderer", command.image->size.x, command.image->size.y, texture->getDepth());

				textureIndex.push_back(texture);
			}
			else
			{
				command.image->allocate(*it);
			}
		}

		if (command.shader == nullptr)
		{
			command.shader = defaultShader;
		}

		queue[queueIndex] = command;
		queueIndex++;
	}

	void Renderer::execute(Command& command)
	{
		if (vertexBufferIndex >= maxIndices)
		{
			// if we're exceeding the vertex quota, then reset and begin a new batch.
			endBatch();
			beginBatch();
		}

		// reset the batch if the shader needs changing
		if (activeShader != command.shader)
		{
			endBatch();
			setShader(command.shader);
			beginBatch();
		}

		Image::Allocation texture = command.image->getAllocation();

		int32_t slotIndex = 0;
		bool hasSlot = false;
		for (int32_t i = 0; i < allocatedTextureSlots; i++)
		{
			if (textures[i] == texture.Texture)
			{
				hasSlot = true;
				slotIndex = i;

				break;
			}
		}

		if (hasSlot == false)
		{
			if (textureNextSlot >= allocatedTextureSlots)
			{
				endBatch();
				beginBatch();

				textureNextSlot = 0;
			}

			textures[textureNextSlot] = texture.Texture;
			slotIndex = textureNextSlot;

			textureNextSlot++;
		}

		Vector2f bounds[] = {
			command.bounds.TL, Vector2f(command.bounds.BR.x, command.bounds.TL.y),
			command.bounds.BR, Vector2f(command.bounds.TL.x, command.bounds.BR.y)
		};

		for (size_t i = 0; i < 4; i++)
		{
			verticesHead->position = command.transform * baseVertex[i];
			verticesHead->tint = command.tint;
			verticesHead->texCoords = bounds[i];
			verticesHead->texLayer = (float_t)texture.Layer;
			verticesHead->texIndex = (float_t)slotIndex;

			verticesHead++;
			stats.vertexCount++;
		}

		vertexBufferIndex += 6;
	}

	void Renderer::begin(Mat4f transform)
	{
		if (sceneActive == true)
			throw RenderStateInvalidException("scene", false);

		sceneActive = true;

		projection = transform;
		queueIndex = 0;

		stats = {};
	}

	void Renderer::end()
	{
		if (sceneActive == false)
			throw RenderStateInvalidException("scene", true);

		sceneActive = false;


		// TODO: swap this out for a render tree

		std::sort(queue, queue + queueIndex,
			[&](const Command& A, const Command& B)
			{
				/*
					first, check if the z-indexes are different. sort by them if they are, as they must be on the
					same index to make optimisation exceptions.

					second, check if the shader being used is of a different ID (using less than), if it is then
					we can batch them into one call when switching shaders.

					lastly, check if the textures are different. if they're not, then batch them. we shouldn't
					have to perform many texture switches, but if we do, then this optimisation may be important!
				*/

				if (A.zIndex < B.zIndex)
				{
					return true;
				}
				else if (A.zIndex == B.zIndex)
				{
					if (A.shader->getInternalId() < B.shader->getInternalId())
					{
						return true;
					}
					else if (A.shader->getInternalId() == B.shader->getInternalId())
					{
						if (A.image->getAllocation().Texture->GetRenderID() < B.image->getAllocation().Texture->GetRenderID())
						{
							return true;
						}
					}
				}

				return false;
			}
		);

		setShader(defaultShader);
		
		if (queueIndex > 0)
		{
			beginBatch();

			for (uint i = 0; i < queueIndex; i++)
			{
				execute(*(queue + i));
			}

			endBatch();
		}
	}

	void Renderer::setShader(Shader* shader)
	{
		if (shader != activeShader)
			activeShader = shader;
		
		activeShader->set("samplers", samplers, allocatedTextureSlots);
		activeShader->set("projection", projection);
	}

	void Renderer::beginBatch()
	{
		if (batchActive == true)
			throw RenderStateInvalidException("batch", false);

		batchActive = true;

		setShader(activeShader);
		
		vertexBufferIndex = 0;
		verticesHead = vertices;
	}

	void Renderer::endBatch()
	{
		if (batchActive == false)
			throw RenderStateInvalidException("batch", true);

		batchActive = false;

		for (uint i = 0; i < textureNextSlot; i++)
		{
			textures[i]->Bind(i);
		}

		if (vertexBufferIndex > 0)
		{
			auto size = bytelen(vertices, verticesHead);
			vertexBatch->Set(vertices, size);
			
			activeShader->bind();
			batchArray->Bind();

			glDrawElements(GL_TRIANGLES, vertexBufferIndex, GL_UNSIGNED_INT, nullptr);
			stats.drawCalls++;
		}
	}

	void Renderer::setViewportSize(Vector2i size)
	{
		glViewport(0, 0, size.x, size.y);
	}

}