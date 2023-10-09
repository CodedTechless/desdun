
#include <include/glew/glew.h>

#include "vao.h"

namespace Desdun 
{
	
	VertexArray::VertexArray() 
	{
		glCreateVertexArrays(1, &RenderID);
	}

	VertexArray::~VertexArray() 
	{
		glDeleteVertexArrays(1, &RenderID);
	}

	Ref<VertexArray> VertexArray::make()
	{
		return CreateRef<VertexArray>();
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(RenderID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetIndexBuffer(Ref<IndexBuffer> iBuffer)
	{
		Bind();
		iBuffer->Bind();

		CurrentIndexBuffer = iBuffer;
	}

	void VertexArray::PushVertexBuffer(Ref<VertexBuffer> vBuffer)
	{
		Bind();
		vBuffer->Bind(); // the arrays are now linked. apply the attributes and stuff

		const auto& Layout = vBuffer->GetLayout();
		const auto& Elements = Layout.GetElements();

		uint Offset = 0;
		for (const auto& Element : Elements)
		{
			glEnableVertexAttribArray(CurrentBufferIndex);
			glVertexAttribPointer(CurrentBufferIndex, Element.Count, (int)Element.Type, Element.Normalised ? GL_TRUE : GL_FALSE, Layout.GetStride(), (const void*)Offset);

			CurrentBufferIndex++;

			Offset += Element.Count * LayoutElement::GetSize(Element.Type);
		}

		VertexBuffers.push_back(vBuffer);
	}


}