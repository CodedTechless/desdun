#pragma once

#include "index.hpp"
#include "vertex.hpp"

#include <corelib/core.hpp>

namespace DesdunCore
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
