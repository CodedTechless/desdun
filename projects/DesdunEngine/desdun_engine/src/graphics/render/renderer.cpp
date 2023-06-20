
#include <desdun_engine/src/app/debug/debug.h>
#include <desdun_engine/src/app/resource/resource.hpp>

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

		// Batch Renderer Setup

		textures = new Ref<TextureArray>[allocatedTextureSlots];
		queue = new Command[commandQueueSize];
		vertices = new Vertex[maxVertices];
		samplers = new int[allocatedTextureSlots];

		uint* indexBuffer = new uint[maxIndices];

		batchArray = CreateRef<VertexArray>();
		verticesHead = vertices;

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

		indexBatch = CreateRef<IndexBuffer>(indexBuffer, maxIndices);
		delete[] indexBuffer;

		// Create the vertex buffer and set its layout.
		vertexBatch = CreateRef<VertexBuffer>(maxVertices * sizeof(Vertex));
		vertexBatch->SetBufferLayout({ // Create a layout for data that is held in the vertex buffer for drawing.
			{ LayoutType::Float, 3 }, // Position
			{ LayoutType::Float, 4 }, // Colour
			{ LayoutType::Float, 2 },
			{ LayoutType::Float, 1 },
			{ LayoutType::Float, 1 }
		});

		// Add the vertex and index buffer to the vertex array.
		batchArray->PushVertexBuffer(vertexBatch);
		batchArray->SetIndexBuffer(indexBatch);

		for (int i = 0; i < allocatedTextureSlots; i++)
		{
			samplers[i] = i;
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

				Debug::Log("Allocted a new texture array of size " + std::to_string(command.image->size.x) + "*" + std::to_string(command.image->size.y) + "*" + std::to_string(texture->getDepth()));

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

		uint32_t slotIndex = 0;
		bool hasSlot = false;
		for (uint32_t i = 0; i < allocatedTextureSlots; i++)
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
			statVertices++;
		}

		vertexBufferIndex += 6;
	}

	void Renderer::begin(Mat4f transform)
	{
		projection = transform;
		queueIndex = 0;

		statVertices = 0;
		statDrawCalls = 0;
		
		setShader(defaultShader);
		beginBatch();
	}

	void Renderer::end()
	{
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

				return A.zIndex < B.zIndex ||
					(A.zIndex == B.zIndex && A.shader->getInternalId() < B.shader->getInternalId()) ||
					((A.zIndex == B.zIndex && A.shader->getInternalId() == B.shader->getInternalId()) &&
					(A.image->getAllocation().Texture->GetRenderID() < B.image->getAllocation().Texture->GetRenderID()));
			}
		);

		for (uint i = 0; i < queueIndex; i++)
		{
			execute(*(queue + i));
		}

		endBatch();
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
		if (active == true)
		{
			throw Exception("Rendering Error: Batch already active");
		}

		active = true;

		setShader(activeShader);
		
		vertexBufferIndex = 0;
		verticesHead = vertices;
	}

	void Renderer::endBatch()
	{
		if (active == false)
		{
			throw Exception("Rendering Error: Batch not active");
		}

		active = false;

		if (vertexBufferIndex == 0)
			return;

		auto size = (uint32_t)((uint8_t*)verticesHead - (uint8_t*)vertices);
		vertexBatch->Set(vertices, size);

		for (uint i = 0; i < textureNextSlot; i++)
		{
			textures[i]->Bind(i);
		}

		batchArray->Bind();
		activeShader->bind();

		if (target)
		{
			// do something
		}

		glDrawElements(GL_TRIANGLES, vertexBufferIndex, GL_UNSIGNED_INT, nullptr);
		statDrawCalls++;
	}

	void Renderer::setViewportSize(Vector2i size)
	{
		glViewport(0, 0, size.x, size.y);
	}

}