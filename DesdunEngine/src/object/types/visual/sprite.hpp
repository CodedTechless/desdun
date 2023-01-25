#pragma once

#include <object/types/object.h>

#include <graphics/renderer.h>

namespace Desdun
{
	class Sprite : public Object
	{
	public:
		RUNTIME_CLASS_DEF(Sprite);

		Image* image = nullptr;
		Shader* shader = nullptr;

		Color4f tint = { 1.f, 1.f, 1.f, 1.f };

		ImageBounds bounds = {
			{ 0.f, 0.f },
			{ 1.f, 1.f }
		};

		void onFrameUpdate(const float_t delta) override
		{
			Mat4f transform = getInterpTransform()
				* glm::scale(Mat4f(1.f), Vector3f(Vector2f(image->GetSize()), 1.f));

			Renderer::Submit({ transform, tint, bounds, image, shader, zIndex });
		}

	private:

		void serialise(JSONObject& object) const override
		{
			object["imagePath"] = image != nullptr ? image->getPath() : "";
			object["shaderPath"] = shader != nullptr ? shader->getPath() : "";

			object["tint"] = tint;
			object["bounds"] = bounds;

			Object::serialise(object);
		}

		void deserialise(const JSONObject& object) override
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

			Object::deserialise(object);
		}

#if 0
		void Serialise(ByteFile& stream) const
		{
			stream << (SpriteImage ? SpriteImage->GetPath() : std::string(""));
			stream << (SpriteShader ? SpriteShader->GetPath() : std::string(""));

			stream << &Tint;
			stream << &ZIndex;
			stream << &SpriteBounds;

			Object::Serialise(stream);
		}

		void Deserialise(ByteFile& stream)
		{
			std::string imagePath = "";
			stream >> imagePath;

			if (imagePath != "")
				SpriteImage = Resource::Fetch<Image>(imagePath);

			std::string shaderPath = "";
			stream >> shaderPath;

			if (shaderPath != "")
				SpriteShader = Resource::Fetch<Shader>(shaderPath);

			stream >> &Tint;
			stream >> &ZIndex;
			stream >> &SpriteBounds;

			Object::Deserialise(stream);
		}
#endif

	};
}