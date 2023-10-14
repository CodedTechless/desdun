

#include <stb/stb_image.h>

#include "image.hpp"

namespace DesdunCore
{
	Image::Image(Vector2 size, uchar* buf, uint channels, uint bitsPerChannel)
		: size(size), buffer(buf), channels(channels), bitsPerChannel(bitsPerChannel)
	{
	}

	void Image::load()
	{
		stbi_set_flip_vertically_on_load(1);
		buffer = stbi_load(getPath().c_str(), &size.x, &size.y, &channels, 4);
	}

	void Image::unload()
	{
		if (buffer) {
			stbi_image_free(buffer);
		}
	}

	void Image::allocate(Ref<TextureArray> alloc)
	{
		if (size != alloc->GetBaseSize())
		{
			throw AllocationMismatchException(size, alloc->GetBaseSize());
		}

		uint layer = alloc->PushLayer(buffer);
		textureAlloc = alloc;
		textureLayer = layer;
	}

	Vector2i Image::getSize() const
	{
		return size;
	};

	uchar* Image::getBuffer() const
	{
		return buffer;
	}

	Image::ImageContext Image::getContext() const
	{
		return { channels, bitsPerChannel };
	}
	
	Image::Allocation Image::getAllocation() const
	{
		return { textureAlloc, textureLayer };
	}

}