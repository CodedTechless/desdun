
#include <GL/glew.h>
#include <glfw3.h>

#include <app/debug/debug.h>
#include <resource/resource.hpp>

#include <core_lib.hpp>

#include "renderer.h"

namespace Desdun
{
	Renderer::RenderCore Renderer::m_RenderCore = {};

	TextureMap Renderer::Textures = {};
	TextureIndex Renderer::TextureIndex = {};

	void Renderer::Start()
	{
		// Debug Output

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		
		glDebugMessageCallback(Debug::OpenGLMessage, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

		// Modes

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		char* Version = (char*)glGetString(GL_VERSION);
		Debug::Log("OpenGL " + std::string(Version));

		const Color4& c = m_RenderCore.TargetClearColour;
		glClearColor(c.r, c.g, c.b, c.a);

		// Batch Renderer Setup

		m_RenderCore.BatchArray = std::make_shared<VertexArray>();
		m_RenderCore.Quads = new Vertex[Renderer::RenderCore::MaxVertices];

		uint QuadOffset = 0;
		uint* IndexBufferTemplate = new uint[Renderer::RenderCore::MaxIndices];
		
		for (uint i = 0; i < Renderer::RenderCore::MaxIndices; i += 6) 
		{
			IndexBufferTemplate[i + 0] = 0 + QuadOffset;
			IndexBufferTemplate[i + 1] = 1 + QuadOffset;
			IndexBufferTemplate[i + 2] = 2 + QuadOffset;

			IndexBufferTemplate[i + 3] = 0 + QuadOffset;
			IndexBufferTemplate[i + 4] = 2 + QuadOffset;
			IndexBufferTemplate[i + 5] = 3 + QuadOffset;

			QuadOffset += 4;
		}

		m_RenderCore.IndexBatch = CreatePointer<IndexBuffer>(IndexBufferTemplate, Renderer::RenderCore::MaxIndices);
		delete[] IndexBufferTemplate;

		// Create the vertex buffer and set its layout.
		m_RenderCore.VertexBatch = CreatePointer<VertexBuffer>(Renderer::RenderCore::MaxVertices * sizeof(Vertex));
		m_RenderCore.VertexBatch->SetBufferLayout({ // Create a layout for data that is held in the vertex buffer for drawing.
			{ LayoutType::Float, 3 }, // Position
			{ LayoutType::Float, 4 }, // Colour
			{ LayoutType::Float, 2 }, // Texture coordinates
			{ LayoutType::Float, 1 }, // Texture Layer
			{ LayoutType::Float, 1 }  // Texture index
		});

		// Add the vertex and index buffer to the vertex array.
		m_RenderCore.BatchArray->PushVertexBuffer(m_RenderCore.VertexBatch);
		m_RenderCore.BatchArray->SetIndexBuffer(m_RenderCore.IndexBatch);

		// Initialise the texture shader and import the basic shader.
		m_RenderCore.DefaultShader = Resource::Fetch<Shader>("assets/shaders/basic.shader");

		m_RenderCore.TextureSamplers = new int[ALLOCATED_TEXTURE_SLOTS];
		for (int i = 0; i < ALLOCATED_TEXTURE_SLOTS; i++)
		{
			m_RenderCore.TextureSamplers[i] = i;
		}

		SetShader(m_RenderCore.DefaultShader);

		
	}

	void Renderer::Stop()
	{
		glfwTerminate();
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::Submit(const RenderCommand& Command)
	{
		RenderCommand CommandCopy { Command };

		if (CommandCopy.ImageResource->TextureAlloc == nullptr)
		{
			auto it = std::find_if(TextureIndex.begin(), TextureIndex.end(), 
				[&](ptr<TextureArray> array) 
				{ 
					return array->GetBaseSize() == CommandCopy.ImageResource->GetSize(); 
				}
			);

			if (it == TextureIndex.end())
			{
				auto NewTexture = CreatePointer<TextureArray>(CommandCopy.ImageResource->Size, 256);
				CommandCopy.ImageResource->Allocate(NewTexture);

				Debug::Log("Allocted texture space of " + std::to_string(CommandCopy.ImageResource->Size.x) + "*" + std::to_string(CommandCopy.ImageResource->Size.y) + "*256");

				TextureIndex.push_back(NewTexture);
			}
			else
			{
				CommandCopy.ImageResource->Allocate(*it);
			}
		}

		if (CommandCopy.ObjectShader == nullptr)
		{
			CommandCopy.ObjectShader = m_RenderCore.DefaultShader;
		}

		m_RenderCore.RenderQueue[m_RenderCore.CommandIndex] = std::move(CommandCopy);
		m_RenderCore.CommandIndex++;
	}

	void Renderer::Execute(RenderCommand& Command)
	{
		if (m_RenderCore.VertexBufferIndex >= Renderer::RenderCore::MaxIndices)
		{
			// if we're exceeding the vertex quota, then reset and begin a new batch.
			FinishBatch();
			BeginBatch();
		}

		// reset the batch if the shader needs changing
		if (m_RenderCore.RenderShader != Command.ObjectShader)
		{
			FinishBatch();
			BeginBatch(Command.ObjectShader);
		}

		Image::Allocation texture = Command.ImageResource->GetAllocation();

		uint32_t TextureSlotIndex = 0;
		bool HasSlot = false;
		for (uint32_t i = 0; i < ALLOCATED_TEXTURE_SLOTS; i++)
		{
			if (m_RenderCore.Textures[i] == texture.Texture)
			{
				HasSlot = true;
				TextureSlotIndex = i;

				break;
			}
		}

		if (!HasSlot)
		{
			if (m_RenderCore.NextTextureSlot > ALLOCATED_TEXTURE_SLOTS)
			{
				FinishBatch();
				BeginBatch();
			}

			m_RenderCore.Textures[m_RenderCore.NextTextureSlot] = texture.Texture;
			TextureSlotIndex = m_RenderCore.NextTextureSlot;

			m_RenderCore.NextTextureSlot++;
		}

		Vector2f bounds[] = {
			Command.Bounds.TL, Vector2f(Command.Bounds.BR.x, Command.Bounds.TL.y),
			Command.Bounds.BR, Vector2f(Command.Bounds.TL.x, Command.Bounds.BR.y)
		};

		for (size_t i = 0; i < 4; i++)
		{
			m_RenderCore.QuadsHeader->Position = Command.Transform * m_RenderCore.VertexNormal[i];
			m_RenderCore.QuadsHeader->Tint = Command.Tint;
			m_RenderCore.QuadsHeader->TextureCoords = bounds[i];
			m_RenderCore.QuadsHeader->Layer = texture.Layer;
			m_RenderCore.QuadsHeader->TextureIndex = TextureSlotIndex;

			m_RenderCore.QuadsHeader++;
			m_RenderCore.FrameVertices++;
		}

		m_RenderCore.VertexBufferIndex += 6;
	}

	void Renderer::BeginScene(const RenderCamera& camera, Mat4f transform)
	{
		m_RenderCore.CurrentCamera = camera;
		m_RenderCore.ProjectionTransform = transform;
		m_RenderCore.CommandIndex = 0;

		m_RenderCore.FrameVertices = 0;
		m_RenderCore.FrameDrawCalls = 0;
		
		BeginBatch(m_RenderCore.DefaultShader);
	}

	void Renderer::EndScene()
	{
		std::sort(m_RenderCore.RenderQueue.begin(), m_RenderCore.RenderQueue.begin() + m_RenderCore.CommandIndex,
			[&](const RenderCommand& A, const RenderCommand& B)
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
					(A.zIndex == B.zIndex && A.ObjectShader->GetRenderID() < B.ObjectShader->GetRenderID()) ||
					((A.zIndex == B.zIndex && A.ObjectShader->GetRenderID() == B.ObjectShader->GetRenderID()) && 
					(A.ImageResource->GetAllocation().Texture->GetRenderID() < B.ImageResource->GetAllocation().Texture->GetRenderID()));
			}
		);

		for (auto i = m_RenderCore.RenderQueue.begin(); i < m_RenderCore.RenderQueue.begin() + m_RenderCore.CommandIndex; ++i)
		{
			// execute all queued render commands
			Execute(*i);
		}


		//Debug::Log(std::to_string(m_RenderCore.CommandIndex) + " " + std::to_string(m_RenderCore.VertexBufferIndex));

		FinishBatch();
	}

	void Renderer::SetShader(Shader* shader)
	{
		if (shader != m_RenderCore.RenderShader)
			m_RenderCore.RenderShader = shader;
		
		m_RenderCore.RenderShader->SetUniform("Textures", m_RenderCore.TextureSamplers, ALLOCATED_TEXTURE_SLOTS);
		m_RenderCore.RenderShader->SetUniform("Projection", m_RenderCore.ProjectionTransform);
	}

	void Renderer::BeginBatch(Shader* shader)
	{
		if (shader)
			SetShader(shader);

		m_RenderCore.NextTextureSlot = 0;
		m_RenderCore.VertexBufferIndex = 0;
		m_RenderCore.QuadsHeader = m_RenderCore.Quads;
	}

	void Renderer::FinishBatch()
	{
		if (m_RenderCore.VertexBufferIndex == 0)
			return;

		auto Size = (uint32_t)((uint8_t*)m_RenderCore.QuadsHeader - (uint8_t*)m_RenderCore.Quads);
		m_RenderCore.VertexBatch->Set(m_RenderCore.Quads, Size);

		for (uint i = 0; i < m_RenderCore.NextTextureSlot; i++)
		{
			m_RenderCore.Textures[i]->Bind(i);
		}

		m_RenderCore.BatchArray->Bind();
		m_RenderCore.RenderShader->Bind();

		glDrawElements(GL_TRIANGLES, m_RenderCore.VertexBufferIndex, GL_UNSIGNED_INT, nullptr);
		m_RenderCore.FrameDrawCalls++;
	}

	void Renderer::setViewportSize(Vector2i size)
	{
		glViewport(0, 0, size.x, size.y);
	}

}