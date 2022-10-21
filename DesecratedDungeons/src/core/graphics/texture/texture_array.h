#pragma once

#include <libraries.hpp>

namespace Desdun
{

	class Image;

	class TextureArray
	{
	public:

		TextureArray(Vector2i SubImageSize, uint Depth);
		~TextureArray();

		void Bind(uint Slot = 0);
		void Unbind();

		void SetLayer(uint layer, Image* image);

		// Getters

		uint GetRenderID() const { return RenderID; };

		Image* operator[](uint Index)
		{
			return *(Array + Index);
		}

	private:

		uint RenderID = 0;

		Vector2i BaseSize = { 0, 0 };
		uint Layers = 0;

		(Image*)* Array = {};

	};

}