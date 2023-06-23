#pragma once

#include "index.h"
#include "vertex.h"

#include <desdun_engine/include/ddlib/core.hpp>

namespace Desdun
{

	class VertexArray 
	{
	public:
		
		VertexArray();
		~VertexArray();

		static Ref<VertexArray> make();

		void SetIndexBuffer(Ref<IndexBuffer> iBuffer);
		void PushVertexBuffer(Ref<VertexBuffer> vBuffer);

		//		void SetBufferLayout(const VertexBuffer& vBuffer, const VertexBufferLayout& Layout);
		//		VertexBufferLayout SetBufferLayout(const VertexBuffer& vBuffer, std::initializer_list<LayoutElement> LayoutInit);

		void Bind() const;
		void Unbind() const;

	private:
		
		Ref<IndexBuffer> CurrentIndexBuffer;
		List<Ref<VertexBuffer>> VertexBuffers;

	private:

		uint CurrentBufferIndex = 0;
		uint RenderID;

	};
}
