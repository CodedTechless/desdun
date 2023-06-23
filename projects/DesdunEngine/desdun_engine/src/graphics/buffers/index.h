#pragma once

#include <desdun_engine/include/desdun_core.hpp>

namespace Desdun
{

	class IndexBuffer
	{
	public:
		IndexBuffer(const uint* Data, uint Count);
		~IndexBuffer();

		static Ref<IndexBuffer> make(const uint* data, uint count);

		void Bind();
		void Unbind();

		uint GetCount() const { return mCount; };
	private:
		
		uint RendererID;
		uint mCount = 0;
	
	};

}