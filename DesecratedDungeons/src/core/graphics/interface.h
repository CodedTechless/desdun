#pragma once

#include <core/graphics/core/render_camera.h>
#include <core/graphics/core/render_queue.h>

#include <core/graphics/shaders/shader.h>
#include <core/graphics/buffers/framebuffer.h>

namespace Desdun
{
	struct Quad
	{
		Vector3 Position;
		Vector4 Tint;
		Vector2 TextureCoords;
		float TextureIndex;
	};


	class RenderInterface
	{
	public:

		static void Start();
		static void Stop();

		static void BeginScene(const RenderCamera& Camera);
		static void EndScene();

		struct RenderCore
		{
			static constexpr uint MaxQuads = 20000;
			static constexpr uint MaxVerticies = MaxQuads * 4;
			static constexpr uint MaxIndices = MaxQuads * 6;

			ptr<Shader> RenderShader = nullptr;
			ptr<FrameBuffer> RenderFrameBuffer = nullptr;

			uint FrameDrawCalls = 0;
			uint FrameVertices = 0;
		};

	private:

		static RenderCore m_RenderCore;
		static RenderQueue m_RenderQueue;
	};


}