
#include <GL/glew.h>

#include "texture.h"

namespace Desdun
{

	Texture::Texture(ptr<Image> image)
	{
		glGenTextures(1, &RenderID);
		glBindTexture(GL_TEXTURE_2D, RenderID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // sets the filter option when the texture is smaller than the actual image
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // same as above but for bigger textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // horizontal clamping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // horizontal clamping

		auto ImageContext = image->GetContext();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, ImageContext.Size.x, ImageContext.Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->GetBuffer());
		
		glBindTexture(GL_TEXTURE_2D, 0);

		RefImage = image;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &RenderID);
	}

	void Texture::Bind(uint Slot)
	{
		glActiveTexture(GL_TEXTURE0 + Slot);
		glBindTexture(GL_TEXTURE_2D, RenderID);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}