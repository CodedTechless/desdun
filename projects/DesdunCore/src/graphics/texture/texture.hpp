#pragma once

#include <corelib/core.hpp>

namespace DesdunCore
{
	class Texture 
	{
	public:
		Texture(uchar* buffer, Vector2i size);
		~Texture();

		void Bind(uint Slot = 0);
		void Unbind();

		uint GetRenderID() const { return RenderID; };
		
	private:
		uint RenderID;
	
	};
}