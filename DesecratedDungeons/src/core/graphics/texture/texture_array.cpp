
#include <GL/glew.h>

#include "texture_array.h"

namespace Desdun
{

	TextureArray::TextureArray(Vector2i SubImageSize, uint layers)
		: BaseSize(SubImageSize), Layers(layers)
	{
		glGenTextures(1, &RenderID);
		glBindTexture(GL_TEXTURE_2D_ARRAY, RenderID);
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, SubImageSize.x, SubImageSize.y, layers);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

		Array = new ptr<Image>[layers]();
	}

	TextureArray::~TextureArray()
	{
		glDeleteTextures(1, &RenderID);
	}

	void TextureArray::SetLayer(uint layer, ptr<Image> image)
	{
		if (image->GetContext().Size != BaseSize)
		{
			Debug::Error("Image provided was not the same size as the subimage of the texture array.");
			return;
		}

		if (layer > Layers)
		{
			Debug::Error("Attempted to update a layer of a depth higher than " + std::to_string(layer));
		}

		glBindTexture(GL_TEXTURE_2D_ARRAY, RenderID);
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, BaseSize.x, BaseSize.y, layer, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->GetBuffer());
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

		Array[layer] = image;
	}

	void Texture::Bind(uint Slot)
	{
		glActiveTexture(GL_TEXTURE0 + Slot);
		glBindTexture(GL_TEXTURE_2D_ARRAY, RenderID);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

}