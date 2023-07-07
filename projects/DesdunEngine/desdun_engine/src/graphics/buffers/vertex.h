#pragma once

#include <desdun_engine/include/glew/glew.h>
#include <desdun_engine/include/ddlib/core.hpp>

namespace Desdun 
{

	enum class LayoutType 
	{
		Half = GL_HALF_FLOAT,
		Float = GL_FLOAT,
		Int = GL_INT
	};

	struct LayoutElement 
	{
		LayoutType Type;
		uint Count = 1;
		bool Normalised = false;

		static uint GetSize(const LayoutType& Type) 
		{
			switch (Type) 
			{
				case LayoutType::Half:			return 2;
				case LayoutType::Float:			return 4;
				case LayoutType::Int:			return 4;
			}

			return 0;
		};
	};

	class VertexBufferLayout
	{
	public:

		VertexBufferLayout() = default;
		VertexBufferLayout(std::initializer_list<LayoutElement> Init);

		void SetLayout(std::initializer_list<LayoutElement> Elements);

		const std::vector<LayoutElement>& GetElements() const { return Elements; }
		uint GetStride() const { return Stride; }

	private:

		std::vector<LayoutElement> Elements;
		uint Stride = 0;

	};

	class VertexBuffer
	{
	public:

		VertexBuffer(uint Size);
		VertexBuffer(const void* Data, uint Size);
		~VertexBuffer();

		static Ref<VertexBuffer> make(uint size);
		static Ref<VertexBuffer> make(const void* data, uint size);

		void Bind();
		void Unbind();

		void Set(const void* Data, uint Size);

		VertexBufferLayout GetLayout() const { return BufferLayout; };

		void SetBufferLayout(const VertexBufferLayout& Layout);

	private:
		VertexBufferLayout BufferLayout;

		uint RenderID = 0;
	};

}