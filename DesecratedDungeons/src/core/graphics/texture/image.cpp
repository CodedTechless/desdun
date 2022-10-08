

#include <stb_image/stb_image.h>

#include "image.h"

namespace Desdun
{

	ptr<Image> Image::Create(const std::string& FilePath)
	{
		ptr<Image> NewImage = CreatePointer<Image>();
		NewImage->Path = FilePath;

		stbi_set_flip_vertically_on_load(1);
		NewImage->Buffer = stbi_load(FilePath.c_str(), &NewImage->Size.x, &NewImage->Size.y, &NewImage->BitsPerPixel, 4);

		return NewImage;
	}

	ptr<Image> Image::Create(Vector2i size, int bitsPerPixel, uchar* buffer)
	{
		ptr<Image> NewImage = CreatePointer<Image>();

		NewImage->Size = size;
		NewImage->BitsPerPixel = bitsPerPixel;
		NewImage->Buffer = buffer;

		return NewImage;
	}

	Image::~Image()
	{
		if (Buffer) {
			stbi_image_free(Buffer);
		}
	}

}