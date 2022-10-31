#pragma once

#include <core/graphics/core/render_camera.h>
#include <core/graphics/texture/texture_array.h>
#include <core/graphics/buffers/vertex.h>
#include <core/graphics/buffers/vao.h>
#include <core/graphics/buffers/index.h>
#include <core/graphics/buffers/frame.h>

#include <core/resource/types/shader.h>
#include <core/resource/types/image.h>

#include <libraries.hpp>

#define RENDER_QUEUE_SIZE 8192
#define ALLOCATED_TEXTURE_SLOTS 16

namespace Desdun
{

	using TextureMap = std::unordered_map<std::string, ptr<TextureArray>>;
	// to-do: make it so we can use more than 256 of the same sized texture!!!
	using TextureIndex = std::unordered_map<Vector2, ptr<TextureArray>>;

	struct ImageBounds
	{
		Vector2 TL;
		Vector2 BR;
	};

	struct Vertex
	{
		Vector3 Position;
		Vector4 Tint;
		Vector2 TextureCoords;
		float Layer;			// "but matthew!! you could just put this float with TextureCoords" yes ik but i like this more so shut up >:(
		float TextureIndex;
	};

	struct RenderCommand
	{
		Mat4 Transform{ 1.f };
		Vector4 Tint{ 0.f };

		ImageBounds Bounds = {};

		Image* ImageResource = nullptr;
		Shader* ObjectShader = nullptr;

		float ZIndex = 0;
	};

	// we use an array for arena allocation bcos it's better than using a vector here
	typedef std::array<RenderCommand, RENDER_QUEUE_SIZE> RenderCommandQueue;

	class Renderer
	{
	public:

		static void Start();
		static void Stop();

		static void BeginScene(const RenderCamera& camera, Mat4 transform);
		static void EndScene();

		static void Clear();
		static void Submit(const RenderCommand& command);

		struct RenderCore
		{
			// Render Limits

			static constexpr uint MaxQuads = 20000;
			static constexpr uint MaxVertices = MaxQuads * 4;
			static constexpr uint MaxIndices = MaxQuads * 6;	
			// these aren't hard limits, just here to stop us sending too much data and having to allocate buffer space unnecessarily
			// us having to render over 20,000 quads is incredibly unlikely anyway, so...

			// Shaders and Targets

			Shader* DefaultShader = nullptr;
			Shader* RenderShader = nullptr;
			ptr<FrameBuffer> RenderTarget = nullptr;

			Color4 TargetClearColour = Color4(0.1f, 0.1f, 0.1f, 1.f);

			// Quads, Vertices and Indices

			Vertex* Quads = nullptr;
			Vertex* QuadsHeader = nullptr;

			ptr<VertexBuffer> VertexBatch = nullptr;
			ptr<IndexBuffer> IndexBatch = nullptr;

			ptr<VertexArray> BatchArray = nullptr;

			uint VertexBufferIndex = 0;
			Vector4 VertexNormal[4] = { // for caching purposes
				{ -0.5f,  0.5f, 0.f, 1.f },
				{  0.5f,  0.5f, 0.f, 1.f },
				{  0.5f, -0.5f, 0.f, 1.f },
				{ -0.5f, -0.5f, 0.f, 1.f }
			};

			// Frames

			uint FrameDrawCalls = 0;
			uint FrameVertices = 0;

			// Textures

			int* TextureSamplers = nullptr; // a pointer to an array of samplers (16 by default)

			uint NextTextureSlot = 0;
			std::array<ptr<TextureArray>, ALLOCATED_TEXTURE_SLOTS> Textures;

			// Cameras

			RenderCamera CurrentCamera = {};
			Mat4 ProjectionTransform { 1.f };	// the current camera transform as stored when BeginScene is called

			// Commands

			RenderCommandQueue RenderQueue = {};
			uint CommandIndex = 0;
		};

	private:

		static void Execute(RenderCommand& Command);
		static void SetShader(Shader* shader);

		static void BeginBatch(Shader* shader = nullptr);
		static void FinishBatch();

		static RenderCore m_RenderCore;

		static TextureMap Textures;
		static TextureIndex TextureIndex;

	};


}