
#include "vertex.hpp"

namespace Desdun 
{

	VertexBuffer::VertexBuffer(unsigned int Size)
	{
		glGenBuffers(1, &RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, RenderID);
		glBufferData(GL_ARRAY_BUFFER, Size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(const void* Data, unsigned int Size)
	{
		glGenBuffers(1, &RenderID); // generate a new buffer stored at a memory address
		glBindBuffer(GL_ARRAY_BUFFER, RenderID);
		glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &RenderID);
	}

	Ref<VertexBuffer> VertexBuffer::make(uint size)
	{
		return CreateRef<VertexBuffer>(size);
	}

	Ref<VertexBuffer> VertexBuffer::make(const void* data, uint size)
	{
		return CreateRef<VertexBuffer>(data, size);
	}

	void VertexBuffer::Set(const void* Data, unsigned int Size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, RenderID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, Size, Data); // puts data into the array to be drawn
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, RenderID); // binds to that buffer and specifies the type as an array buffer
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::SetBufferLayout(const VertexBufferLayout& Layout)
	{
		BufferLayout = Layout;
	}

	// Buffer Layout

	VertexBufferLayout::VertexBufferLayout(std::initializer_list<LayoutElement> Init)
		: Stride(0), Elements(Init)
	{
		for (auto& Element : Elements) {
			Stride += LayoutElement::GetSize(Element.Type) * Element.Count;
		}
	}

	void VertexBufferLayout::SetLayout(std::initializer_list<LayoutElement> NewElements)
	{
		for (auto& Element : NewElements)
		{
			Elements.push_back(Element);
			Stride += LayoutElement::GetSize(Element.Type) * Element.Count;
		}
	}
}