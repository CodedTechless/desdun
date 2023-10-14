#pragma once

#include <corelib/core.hpp>

namespace DesdunCore
{

	class TextureArray
	{
	public:

		TextureArray(Vector2i SubImageSize, uint Depth);
		~TextureArray();

		void Bind(uint Slot = 0);
		void Unbind();

		uint PushLayer(uchar* buffer);

		// Getters

		Vector2i GetBaseSize() const { return BaseSize; };
		uint getDepth() const { return Layers; };
		uint GetRenderID() const { return RenderID; };

		uint Size() const;

		uchar* operator[](uint Index)
		{
			return *(Array + Index);
		}

	private:

		uint RenderID = 0;

		Vector2i BaseSize = { 0, 0 };
		uint Layers = 0;

		uchar** Array;
		uint ArraySize;

		friend class Renderer;
	};

}