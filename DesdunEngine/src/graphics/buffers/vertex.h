#pragma once

#include <GL/glew.h>

#include <core_lib.hpp>

namespace Desdun 
{

	enum class LayoutType 
	{
		Float = GL_FLOAT,
		Int = GL_INT,
		UnsignedInt = GL_UNSIGNED_INT,
		UnsignedByte = GL_UNSIGNED_BYTE
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
				case LayoutType::Float:			return 4;
				case LayoutType::Int:			return 4;
				case LayoutType::UnsignedInt:	return 4;
				case LayoutType::UnsignedByte:	return 1;
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