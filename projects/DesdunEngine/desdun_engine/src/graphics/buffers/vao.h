#pragma once

#include "index.h"
#include "vertex.h"

#include <desdun_engine/include/desdun_core.hpp>

namespace Desdun
{

	class VertexArray {
	public:
		
		VertexArray();
		~VertexArray();

		void SetIndexBuffer(ptr<IndexBuffer> iBuffer);
		void PushVertexBuffer(ptr<VertexBuffer> vBuffer);

		//		void SetBufferLayout(const VertexBuffer& vBuffer, const VertexBufferLayout& Layout);
		//		VertexBufferLayout SetBufferLayout(const VertexBuffer& vBuffer, std::initializer_list<LayoutElement> LayoutInit);

		void Bind() const;
		void Unbind() const;

	private:
		
		ptr<IndexBuffer> CurrentIndexBuffer;
		std::vector<ptr<VertexBuffer>> VertexBuffers;

	private:

		uint CurrentBufferIndex = 0;
		uint RenderID;

	};
}
