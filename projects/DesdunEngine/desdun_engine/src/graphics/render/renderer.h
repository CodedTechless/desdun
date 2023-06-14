#pragma once

#include <desdun_engine/src/graphics/render/render_camera.h>
#include <desdun_engine/src/graphics/texture/texture_array.h>
#include <desdun_engine/src/graphics/buffers/vertex.h>
#include <desdun_engine/src/graphics/buffers/vao.h>
#include <desdun_engine/src/graphics/buffers/index.h>
#include <desdun_engine/src/graphics/buffers/frame.h>

#include <desdun_engine/src/app/resource/descendants/shader.h>
#include <desdun_engine/src/app/resource/descendants/image.h>

#include <desdun_engine/include/desdun_core.hpp>

#define RENDER_QUEUE_SIZE 8192
#define ALLOCATED_TEXTURE_SLOTS 16

namespace Desdun
{

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

	// we use an array for arena allocation bcos it's better than using a vector here

	class Renderer
	{
	public:
		Renderer(Shader* shaderDefault);
		~Renderer() = default;

		struct FrameData
		{
			uint vertexCount;
			uint drawCalls;
			String shaderPath;
		};

		struct Vertex
		{
			Vector3f position;
			Vector4f tint;
			Vector4f textureCoords; // x, y, layer, index
		};

		struct Command
		{
			Mat4f transform { 1.f };
			Color4f tint { 0.f };
			
			ImageBounds bounds = {};

			Image* image = nullptr;
			Shader* shader = nullptr;

			float zIndex = 0;
		};

		using TextureMap = Map<String, Ref<TextureArray>>;
		// TODO: make it so we can use more than 256 of the same sized texture!!!
		using TextureIndex = List<Ref<TextureArray>>;
		using CommandQueue = Array<Command, RENDER_QUEUE_SIZE>;

		Color4 targetColour = Color4(0.1f, 0.1f, 0.1f, 1.f);

		void begin(Mat4f transform);
		void end();

		void clear();
		void setViewportSize(Vector2i size);

		void enqueue(const Command& command);

		FrameData getFrameData() const
		{
			return {
				statVertices,
				statDrawCalls,
				activeShader ? activeShader->getPath() : "none"
			};
		};

	private:

		bool active = false;
		
		Shader* defaultShader = nullptr;
		Shader* activeShader = nullptr;
		
		uint maxQuads = 20000;
		uint maxVertices = maxQuads * 4;
		uint maxIndices = maxQuads * 6;

		static constexpr Vector4 baseVertex[4] = {
			{ -0.5f,  0.5f, 0.f, 1.f },
			{  0.5f,  0.5f, 0.f, 1.f },
			{  0.5f, -0.5f, 0.f, 1.f },
			{ -0.5f, -0.5f, 0.f, 1.f }
		};

		Ref<FrameBuffer> target = nullptr;
		
		// quads

		Vertex* vertices = nullptr;
		Vertex* verticesHead = nullptr;

		// buffers

		Ref<VertexBuffer> vertexBatch = nullptr;
		Ref<IndexBuffer> indexBatch = nullptr;
		Ref<VertexArray> batchArray = nullptr;

		uint vertexBufferIndex = 0;

		// stats

		uint statDrawCalls = 0;
		uint statVertices = 0;

		// textures

		int* samplers = nullptr;

		uint maxTextureArrayDepth = 256;
		uint textureNextSlot = 0;
		Array<Ref<TextureArray>, ALLOCATED_TEXTURE_SLOTS> textures;

		TextureMap texturesMapped = {};
		TextureIndex textureIndex = {};

		RenderCamera currentCamera = {};
		Mat4f projection{ 1.f };

		// Commands

		CommandQueue queue = {};
		uint queueIndex = 0;

		void execute(Command& command);
		void setShader(Shader* shader);

		void beginBatch();
		void endBatch();

	};


}