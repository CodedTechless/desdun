#pragma once

#include <core/graphics/texture/texture.h>
#include <core/graphics/texture/image.h>

#include <libraries.hpp>

namespace Desdun
{

	class TextureArray
	{
	public:

		TextureArray(Vector2i SubImageSize, uint Depth);
		~TextureArray();

		void Bind(uint Slot = 0);
		void Unbind();

		void SetLayer(uint layer, ptr<Image> image);

		uint GetRenderID() const { return RenderID; };

		ptr<Image> operator[](uint Index)
		{
			return *(Array + Index);
		}

	private:

		uint RenderID = 0;

		Vector2i BaseSize = { 0, 0 };
		uint Layers = 0;

		ptr<Image>* Array = {};

	};

}