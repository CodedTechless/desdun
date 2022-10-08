#pragma once

#include <core/graphics/texture/image.h>

#include <libraries.hpp>

namespace Desdun
{
	class Texture 
	{
	public:
		Texture() = default;
		Texture(ptr<Image> image);
		~Texture();

		void Bind(uint Slot = 0);
		void Unbind();

		uint GetRenderID() const { return RenderID; };
		
	private:
		uint RenderID = 0;
		ptr<Image> RefImage = nullptr;
	};
}