

#include "index.h"

namespace Desdun
{
	IndexBuffer::IndexBuffer(const uint* Data, uint Count)
		: mCount(Count)
	{
		glGenBuffers(1, &RendererID); // generate a new buffer stored at a memory address
		glBindBuffer(GL_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ARRAY_BUFFER, mCount * sizeof(uint), Data, GL_STATIC_DRAW); // puts index information into the buffer
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &RendererID);
	}

	Ref<IndexBuffer> IndexBuffer::make(const uint* data, uint count)
	{
		return CreateRef<IndexBuffer>(data, count);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID); // binds to that buffer and specifies the type as an element array buffer
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // binds to that buffer and specifies the type as an element array buffer
	}
}