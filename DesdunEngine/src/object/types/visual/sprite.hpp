#pragma once

#include <object/types/object.h>

#include <graphics/renderer.h>

namespace Desdun
{
	class Sprite : public Object
	{
	public:
		RUNTIME_CLASS_DEF(Sprite);

		Image* SpriteImage = nullptr;
		Shader* SpriteShader = nullptr;

		Color4f Tint = { 1.f, 1.f, 1.f, 1.f };

		ImageBounds SpriteBounds = {
			{ 0.f, 0.f },
			{ 1.f, 1.f }
		};

		void onFrameUpdate(const float_t delta) override
		{
			Mat4f transform = getInterpTransform()
				* glm::scale(Mat4f(1.f), Vector3f(Vector2f(SpriteImage->GetSize()), 1.f));

			Renderer::Submit({ transform, Tint, SpriteBounds, SpriteImage, SpriteShader, zIndex });
		}

	private:

		void serialise(JSONObject& object) const override
		{
			object["SpriteImagePath"] = SpriteImage != nullptr ? SpriteImage->GetPath() : "";
			object["SpriteShaderPath"] = SpriteShader != nullptr ? SpriteShader->GetPath() : "";

			object["Tint"] = Tint;
			object["SpriteBounds"] = SpriteBounds;

			Object::serialise(object);
		}

		void deserialise(const JSONObject& object) override
		{
			std::string spriteImage = object.at("SpriteImagePath").get<std::string>();
			if (spriteImage != "")
			{
				SpriteImage = Resource::Fetch<Image>(spriteImage);
			}

			std::string shaderImage = object.at("SpriteShaderPath").get<std::string>();
			if (shaderImage != "")
			{
				SpriteShader = Resource::Fetch<Shader>(shaderImage);
			}

			object.at("Tint").get_to(Tint);
			object.at("SpriteBounds").get_to(SpriteBounds);

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