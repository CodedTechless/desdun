
#include <glew/glew.h>

#include "texture_array.hpp"

namespace Desdun
{

	TextureArray::TextureArray(Vector2i SubImageSize, uint layers)
		: BaseSize(SubImageSize), Layers(layers)
	{
		glGenTextures(1, &RenderID);
		glBindTexture(GL_TEXTURE_2D_ARRAY, RenderID);
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, SubImageSize.x, SubImageSize.y, layers);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

		Array = new uchar*[layers];
		ArraySize = 0;
	}

	TextureArray::~TextureArray()
	{
		glDeleteTextures(1, &RenderID);
	}

	uint TextureArray::Size() const
	{
		return ArraySize;
	}

	uint TextureArray::PushLayer(uchar* buffer)
	{
		if (ArraySize > Layers)
		{
			assert(false);
		}

		glBindTexture(GL_TEXTURE_2D_ARRAY, RenderID);
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, ArraySize, BaseSize.x, BaseSize.y, 1, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		
		Array[ArraySize] = buffer;
		
		return ArraySize++;
	}

	void TextureArray::Bind(uint Slot)
	{
		glActiveTexture(GL_TEXTURE0 + Slot);
		glBindTexture(GL_TEXTURE_2D_ARRAY, RenderID);
	}

	void TextureArray::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

}