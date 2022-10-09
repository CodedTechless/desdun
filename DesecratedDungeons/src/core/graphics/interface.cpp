
#include <core/debug/debug.h>

#include <GL/glew.h>
#include <glfw3.h>

#include <libraries.hpp>

#include "interface.h"


namespace Desdun
{
	RenderInterface::RenderCore RenderInterface::m_RenderCore = {};

	void RenderInterface::Start()
	{
		// Debug Output

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		
		glDebugMessageCallback(Debug::OpenGLMessage, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

		// Modes

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		const Color4& c = m_RenderCore.TargetClearColour;
		glClearColor(c.r, c.g, c.b, c.a);

		// Batch Renderer Setup

		m_RenderCore.BatchArray = std::make_shared<VertexArray>();
		m_RenderCore.Quads = new Quad[RenderInterface::RenderCore::MaxVertices];

		uint QuadOffset = 0;
		uint* IndexBufferTemplate = new uint[RenderInterface::RenderCore::MaxIndices];
		
		for (uint i = 0; i < RenderInterface::RenderCore::MaxIndices; i += 6) 
		{
			IndexBufferTemplate[i + 0] = 0 + QuadOffset;
			IndexBufferTemplate[i + 1] = 1 + QuadOffset;
			IndexBufferTemplate[i + 2] = 2 + QuadOffset;

			IndexBufferTemplate[i + 3] = 0 + QuadOffset;
			IndexBufferTemplate[i + 4] = 2 + QuadOffset;
			IndexBufferTemplate[i + 5] = 3 + QuadOffset;

			QuadOffset += 4;
		}

		m_RenderCore.IndexBatch = CreatePointer<IndexBuffer>(IndexBufferTemplate, RenderInterface::RenderCore::MaxIndices);
		delete[] IndexBufferTemplate;

		// Create the vertex buffer and set its layout.
		m_RenderCore.VertexBatch = CreatePointer<VertexBuffer>(RenderInterface::RenderCore::MaxVertices * sizeof(Quad));
		m_RenderCore.VertexBatch->SetBufferLayout({ // Create a layout for data that is held in the vertex buffer for drawing.
			{ LayoutType::Float, 3 }, // Position
			{ LayoutType::Float, 4 }, // Colour
			{ LayoutType::Float, 2 }, // Texture coordinates
			{ LayoutType::UnsignedInt, 1 }, // Texture Layer
			{ LayoutType::UnsignedInt, 1 }  // Texture index
		});

		// Add the vertex and index buffer to the vertex array.
		m_RenderCore.BatchArray->PushVertexBuffer(m_RenderCore.VertexBatch);
		m_RenderCore.BatchArray->SetIndexBuffer(m_RenderCore.IndexBatch);

		// Initialise the texture shader and import the basic shader.
		m_RenderCore.DefaultShader = std::make_shared<Shader>();
		m_RenderCore.DefaultShader->Import("assets/shaders/basic.shader");
		m_RenderCore.DefaultShader->Bind();

		SetShader(m_RenderCore.DefaultShader);
	}

	void RenderInterface::Stop()
	{
		glfwTerminate();
	}

	void RenderInterface::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderInterface::Submit(const RenderCommand& Command)
	{
		m_RenderCore.RenderQueue[m_RenderCore.CommandIndex] = Command;
		m_RenderCore.CommandIndex++;
	}

	void RenderInterface::Execute(RenderCommand& Command)
	{
		if (m_RenderCore.VertexBufferIndex >= RenderInterface::RenderCore::MaxIndices)
		{
			// if we're exceeding the vertex quota, then reset and begin a new batch.
			FinishBatch();
			BeginBatch();
		}

		if (!Command.ObjectShader)
		{
			if (m_RenderCore.RenderShader != m_RenderCore.DefaultShader)
			{
				// if there's no defined ObjectShader and the current shader isn't the default one,
				// then switch back to the default shader.
				FinishBatch();
				BeginBatch(m_RenderCore.DefaultShader);
			}
		}
		else
		{
			// if there is an object shader, then reset the batch and use the new shader.
			if (m_RenderCore.RenderShader != Command.ObjectShader)
			{
				FinishBatch();
				BeginBatch(Command.ObjectShader);
			}
		}

		uint32_t TextureSlotIndex = 0;
		for (uint32_t i = 0; i < ALLOCATED_TEXTURE_SLOTS; i++)
		{
			if (m_RenderCore.Textures[i] == Command.ObjectTexture)
			{
				TextureSlotIndex = i;
			}
		}

		if (TextureSlotIndex == 0)
		{
			if (m_RenderCore.NextTextureSlot > ALLOCATED_TEXTURE_SLOTS)
			{
				FinishBatch();
				BeginBatch();
			}

			m_RenderCore.Textures[m_RenderCore.NextTextureSlot] = Command.ObjectTexture;
			TextureSlotIndex = m_RenderCore.NextTextureSlot;

			m_RenderCore.NextTextureSlot++;
		}

		for (size_t i = 0; i < 4; i++)
		{
			m_RenderCore.QuadsHeader->Position = Command.Transform * m_RenderCore.VertexNormal[i];
			m_RenderCore.QuadsHeader->Tint = Command.Tint;
			m_RenderCore.QuadsHeader->TextureCoords = Command.ObjectTextureCoords[i];
			m_RenderCore.QuadsHeader->Layer = Command.ObjectTextureLayer;
			m_RenderCore.QuadsHeader->TextureIndex = TextureSlotIndex;

			m_RenderCore.QuadsHeader++;
		}

		m_RenderCore.VertexBufferIndex += 6;
	}

	void RenderInterface::BeginScene(const RenderCamera& Camera)
	{
		BeginBatch(m_RenderCore.DefaultShader);

		m_RenderCore.CurrentCamera = Camera;
		m_RenderCore.CommandIndex = 0;
	}

	void RenderInterface::EndScene()
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

				return A.ZIndex < B.ZIndex ||
					(A.ZIndex == B.ZIndex && A.ObjectShader->GetRenderID() < B.ObjectShader->GetRenderID()) ||
					((A.ZIndex == B.ZIndex && A.ObjectShader->GetRenderID() == B.ObjectShader->GetRenderID()) && 
					(A.ObjectTexture->GetRenderID() < B.ObjectTexture->GetRenderID()));
			}
		);

		for (auto i = m_RenderCore.RenderQueue.begin(); i < m_RenderCore.RenderQueue.begin() + m_RenderCore.CommandIndex; ++i)
		{
			// execute all queued render commands
			Execute(*i);
		}

		FinishBatch();
	}

	void RenderInterface::SetShader(ptr<Shader> shader)
	{
		int* Samplers = new int[ALLOCATED_TEXTURE_SLOTS];
		for (int i = 0; i < ALLOCATED_TEXTURE_SLOTS; i++)
		{
			Samplers[i] = i;
		}

		if (shader != m_RenderCore.RenderShader)
			m_RenderCore.RenderShader = shader;

		const RenderCamera& Camera = m_RenderCore.CurrentCamera;
		Mat4 Proj = Camera.GetProjectionTransform();
		
		m_RenderCore.RenderShader->SetUniform("Textures", Samplers, ALLOCATED_TEXTURE_SLOTS);
		m_RenderCore.RenderShader->SetUniform("Projection", Proj);
	}

	void RenderInterface::BeginBatch(ptr<Shader> shader)
	{
		if (shader)
			SetShader(shader);

		m_RenderCore.NextTextureSlot = 0;
		m_RenderCore.VertexBufferIndex = 0;
		m_RenderCore.QuadsHeader = m_RenderCore.Quads;
	}

	void RenderInterface::FinishBatch()
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
	}

}