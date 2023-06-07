#pragma once

#include <src/graphics/render/render_camera.h>
#include <src/graphics/texture/texture_array.h>
#include <src/graphics/buffers/vertex.h>
#include <src/graphics/buffers/vao.h>
#include <src/graphics/buffers/index.h>
#include <src/graphics/buffers/frame.h>

#include <src/app/resource/descendants/shader.h>
#include <src/app/resource/descendants/image.h>

#include <include/desdun_engine.hpp>

#define RENDER_QUEUE_SIZE 8192
#define ALLOCATED_TEXTURE_SLOTS 16

namespace Desdun
{

	using TextureMap = Map<String, Ref<TextureArray>>;
	// to-do: make it so we can use more than 256 of the same sized texture!!!
	using TextureIndex = List<Ref<TextureArray>>;

	struct ImageBounds
	{
		Vector2f TL;
		Vector2f BR;

		friend void to_json(json& object, const ImageBounds& bounds)
		{
			object = json::array({
				bounds.TL,
				bounds.BR
			});
		};

		friend void from_json(const json& object, ImageBounds& bounds)
		{
			bounds = {
				object[0],
				object[1]
			};
		}
	};

	struct Vertex
	{
		Vector3f Position;
		Vector4f Tint;
		Vector2f TextureCoords;
		float Layer;			// "but matthew!! you could just put this float with TextureCoords" yes ik but i like this more so shut up >:(
		float TextureIndex;
	};

	struct RenderCommand
	{
		Mat4f Transform{ 1.f };
		Color4f Tint{ 0.f };

		ImageBounds Bounds = {};

		Image* ImageResource = nullptr;
		Shader* ObjectShader = nullptr;

		float zIndex = 0;
	};

	struct FrameData
	{
		uint vertexCount;
		uint drawCalls;
	};

	// we use an array for arena allocation bcos it's better than using a vector here
	typedef Array<RenderCommand, RENDER_QUEUE_SIZE> RenderCommandQueue;

	class Renderer
	{
	public:

		static void start();
		static void stop();

		static void BeginScene(Mat4f transform);
		static void EndScene();

		static void setViewportSize(Vector2i size);

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
			Ref<FrameBuffer> RenderTarget = nullptr;

			Color4 TargetClearColour = Color4(0.1f, 0.1f, 0.1f, 1.f);

			// Quads, Vertices and Indices

			Vertex* Quads = nullptr;
			Vertex* QuadsHeader = nullptr;

			Ref<VertexBuffer> VertexBatch = nullptr;
			Ref<IndexBuffer> IndexBatch = nullptr;

			Ref<VertexArray> BatchArray = nullptr;

			uint VertexBufferIndex = 0;
			Vector4 VertexNormal[4] = {
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
			Array<Ref<TextureArray>, ALLOCATED_TEXTURE_SLOTS> Textures;

			uint maxTextureArrayDepth = 256;

			// Cameras

			RenderCamera CurrentCamera = {};
			Mat4f ProjectionTransform { 1.f };	// the current camera transform as stored when BeginScene is called

			// Commands

			RenderCommandQueue RenderQueue = {};
			uint CommandIndex = 0;
		};

		static FrameData getFrameData()
		{
			return { 
				m_RenderCore.FrameVertices, 
				m_RenderCore.FrameDrawCalls
			};
		}

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