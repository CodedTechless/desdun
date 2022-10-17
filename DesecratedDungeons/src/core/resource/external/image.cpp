

#include <stb_image/stb_image.h>

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

	void Image::Load(const std::string& path)
	{
		Path = path;

		stbi_set_flip_vertically_on_load(1);
		Buffer = stbi_load(Path.c_str(), &Size.x, &Size.y, &BitsPerPixel, 4);
	}

}