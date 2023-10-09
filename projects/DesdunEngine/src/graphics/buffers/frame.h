#pragma once

#include <include/ddlib/core.hpp>

namespace Desdun
{

	enum class FrameBufferFormat
	{
		None,
		RGBA8,
		DEPTH24STENCIL8
	};

	struct FrameBufferSpecification
	{
		Vector2u Size;
		std::vector<FrameBufferFormat> Attachments;

		uint Samples = 1;
		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		FrameBuffer(const FrameBufferSpecification& spec);
		~FrameBuffer();

		void Clear();
		void Invalidate();
		void Resize(const glm::u32vec2& Size);

		void Bind();
		void Unbind();

		inline FrameBufferSpecification& GetSpecification() { return Specification; };
		inline uint GetColourAttachmentRendererID(size_t index = 0) { return ColourRenderAttachments[index]; };

	private:
		std::vector<FrameBufferFormat> ColourFormat;
		std::vector<uint> ColourRenderAttachments = {};

		FrameBufferFormat DepthFormat = FrameBufferFormat::None;
		uint DepthRenderAttachment = 0;

		uint RenderID = 0;

		FrameBufferSpecification Specification;
	};

}
