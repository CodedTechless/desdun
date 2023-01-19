#pragma once

#include <core_lib.hpp>

namespace Desdun
{

	class IndexBuffer
	{
	public:
		IndexBuffer(const uint* Data, uint Count);
		~IndexBuffer();

		void Bind();
		void Unbind();

		uint GetCount() const { return mCount; };
	private:
		
		uint RendererID;
		uint mCount = 0;
	
	};

}