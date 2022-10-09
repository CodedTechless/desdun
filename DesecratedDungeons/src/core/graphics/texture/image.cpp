

#include <stb_image/stb_image.h>

#include "image.h"

namespace Desdun
{

	Image::Image(const std::string& FilePath)
		: Path(FilePath)
	{
		stbi_set_flip_vertically_on_load(1);
		Buffer = stbi_load(FilePath.c_str(), &Size.x, &Size.y, &BitsPerPixel, 4);
	}

	Image::Image(Vector2i size, int bitsPerPixel, uchar* buffer)
		: Size(size), BitsPerPixel(bitsPerPixel), Buffer(buffer)
	{}

	Image::~Image()
	{
		if (Buffer) {
			stbi_image_free(Buffer);
		}
	}

}