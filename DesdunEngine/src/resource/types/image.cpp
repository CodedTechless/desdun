

#include <stb/stb_image.h>

#include "image.h"

namespace Desdun
{

	Image::~Image()
	{
		if (Buffer) {
			stbi_image_free(Buffer);
		}
	}

	/*
	void Image::Push(Vector2i size, int bitsPerPixel, uchar* buffer)
	{
		Size = size;
		BitsPerPixel = bitsPerPixel;
		Buffer = buffer;
	}
	*/

	void Image::Allocate(ptr<TextureArray> alloc)
	{
		if (Size != alloc->GetBaseSize())
		{
			throw new Exception("Tried to allocate an image to a texture array that wasn't the same size.");
		}

		uint layer = alloc->PushLayer(Buffer);

		TextureAlloc = alloc;
		TextureLayer = layer;
	}

	void Image::load(const std::string& path)
	{
		Path = path;

		stbi_set_flip_vertically_on_load(1);
		Buffer = stbi_load(Path.c_str(), &Size.x, &Size.y, &Channels, 4);
	}

}