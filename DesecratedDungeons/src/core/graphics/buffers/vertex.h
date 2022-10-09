#pragma once

#include <GL/glew.h>

#include <libraries.hpp>

namespace Desdun 
{

	enum class LayoutType 
	{
		Float = 5126,
		UnsignedInt = 5125,
		UnsignedByte = 5121
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

		void SetLayout(std::vector<LayoutElement> Elements);

		const std::vector<LayoutElement>& GetElements() const { return Elements; }
		uint GetStride() const { return bStride; }

	private:

		std::vector<LayoutElement> Elements;
		uint bStride = 0;

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