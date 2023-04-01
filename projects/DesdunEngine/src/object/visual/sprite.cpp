
#include "sprite.hpp"


namespace Desdun
{

	void Sprite::onFrameUpdate(float_t delta)
	{
		if (image != nullptr)
		{
			Mat4f transform = glm::translate(Mat4f(1.f), Vector3(offset, 0.f));
			transform *= getRenderTransform();
			transform *= glm::scale(Mat4f(1.f), Vector3f(Vector2f(image->GetSize()), 1.f));

			Renderer::Submit({ transform, tint, { bounds.TL * tiles, bounds.BR * tiles }, image, shader, zIndex });
		}
	}

	void Sprite::serialise(JSONObject& object) const
	{
		object["imagePath"] = image != nullptr ? image->getPath() : "";
		object["shaderPath"] = shader != nullptr ? shader->getPath() : "";

		object["tint"] = tint;
		object["bounds"] = bounds;

		WorldObject::serialise(object);
	}

	void Sprite::deserialise(const JSONObject& object)
	{
		std::string spriteImage = object.at("imagePath").get<std::string>();
		if (spriteImage != "")
		{
			image = Resource::fetch<Image>(spriteImage);
		}

		std::string shaderImage = object.at("shaderPath").get<std::string>();
		if (shaderImage != "")
		{
			shader = Resource::fetch<Shader>(shaderImage);
		}

		object.at("tint").get_to(tint);
		object.at("bounds").get_to(bounds);

		WorldObject::deserialise(object);
	}


}