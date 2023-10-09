#pragma once

#include <src/graphics/render/render_camera.h>
#include <src/graphics/texture/texture_array.h>
#include <src/graphics/buffers/vertex.h>
#include <src/graphics/buffers/vao.h>
#include <src/graphics/buffers/index.h>
#include <src/graphics/buffers/frame.h>

#include <src/resources/descendants/shader.hpp>
#include <src/resources/descendants/image.h>

#include <include/ddlib/core.hpp>

#define RENDER_QUEUE_SIZE 8192
#define ALLOCATED_TEXTURE_SLOTS 16

namespace Desdun
{

	class RenderStateInvalidException : public virtual Exception
	{
	public:
		RenderStateInvalidException(const String& pipe, bool expected)
			: Exception(std::format("{} state incorrect. Expected {}.", pipe, expected ? "active" : "inactive")) {};
	};

	enum class RenderMode
	{
		OpenGL
		// Vulkan
		// Metal
		// DirectX
	};

	class Renderer
	{
	public:
		Renderer(Shader* shaderDefault);
		~Renderer();

		struct Performance
		{
			uint vertexCount = 0;
			uint lineCount = 0;
			uint drawCalls = 0;
		};

		struct Vertex
		{
			Vector3f position;
			Vector4f tint;
			Vector2f texCoords; // x, y, layer, index
			float_t texLayer;
			float_t texIndex;
		};

		struct Command
		{
			Command() = default;
			Command(Command& object) = default;
			Command(const Command& object) = default;


			Mat4f transform{ 1.f };
			Color4f tint{ 0.f };

			ImageBounds bounds = {};

			Image* image = nullptr;
			Shader* shader = nullptr;

			float zIndex = 0;
		};

		Color4 targetColour = Color4(0.1f, 0.1f, 0.1f, 1.f);

		void enqueue(const Command& command);
		void begin(Mat4f transform);
		void end();
		void clear();

		void setViewportSize(Vector2i size);

		Performance performance() const
		{
			return stats;
		};

		// options

		static constexpr uint commandQueueSize = RENDER_QUEUE_SIZE;
		static constexpr uint allocatedTextureSlots = ALLOCATED_TEXTURE_SLOTS;
		static constexpr uint maxTextureArrayDepth = 256;

		static constexpr uint maxQuads = 20000;
		static constexpr uint maxVertices = maxQuads * 4;
		static constexpr uint maxIndices = maxQuads * 6;

		static constexpr Vector4 baseVertex[4] = {
			{ -0.5f,  0.5f, 0.f, 1.f },
			{  0.5f,  0.5f, 0.f, 1.f },
			{  0.5f, -0.5f, 0.f, 1.f },
			{ -0.5f, -0.5f, 0.f, 1.f }
		};

	private:

		RenderMode mode = RenderMode::OpenGL;

		bool sceneActive = false;
		bool batchActive = false;

		Performance stats = {};

		// shaders

		Shader* defaultShader = nullptr;
		Shader* activeShader = nullptr;

		int* samplers = nullptr;

		// frame buffers

		Ref<FrameBuffer> target = nullptr;
		
		// buffers

		// # quads
		Vertex* vertices = nullptr;
		Vertex* verticesHead = nullptr;

		Ref<VertexBuffer> vertexBatch = nullptr;
		Ref<IndexBuffer> indexBatch = nullptr;
		Ref<VertexArray> batchArray = nullptr;

		uint vertexBufferIndex = 0;

		// textures

		uint textureNextSlot = 0;

		Ref<TextureArray>* textures = {};

		Map<String, Ref<TextureArray>> texturesMapped = {};
		List<Ref<TextureArray>> textureIndex = {};

		Mat4f projection { 1.f };

		// commands

		Command* queue = nullptr;
		uint queueIndex = 0;

		void execute(Command& command);
		void setShader(Shader* shader);

		// batches

		void beginBatch();
		void endBatch();

	};


}