#pragma once

#include <object/object.h>

#include <graphics/renderer.h>

using namespace Desdun;

class Sprite : public Object
{
public:
	CLASS_DEF("Sprite");

	Image* SpriteImage = nullptr;
	Color4 Tint = { 1.f, 1.f, 1.f, 1.f };

	Shader* SpriteShader = nullptr;

	float ZIndex = 0;

	ImageBounds SpriteBounds = {
		{ 0.f, 0.f },
		{ 1.f, 1.f }
	};

	void OnFrameUpdate(const float delta) override
	{
		Mat4 transform = GetInterpTransform() 
			* glm::scale(Mat4(1.f), Vector3(Vector2(SpriteImage->GetSize()), 1.f));

		Renderer::Submit({ transform, Tint, SpriteBounds, SpriteImage, SpriteShader, ZIndex });
	}

private:

	void Serialise(ByteFile& stream)
	{
		if (SpriteImage)
			stream << SpriteImage->GetPath();
		else
			stream << std::string("");

		if (SpriteShader)
			stream << SpriteShader->GetPath();
		else
			stream << std::string("");

		stream << &Tint;
		stream << &ZIndex;
		stream << &SpriteBounds;

		Object::Serialise(stream);
	}

	void Deserialise(ByteFile& stream)
	{
		std::string imagePath;
		stream >> imagePath;

		if (imagePath != "")
			SpriteImage = Resource::Fetch<Image>(imagePath);

		std::string shaderPath;
		stream >> shaderPath;

		if (shaderPath != "")
			SpriteShader = Resource::Fetch<Shader>(shaderPath);

		stream >> &Tint;
		stream >> &ZIndex;
		stream >> &SpriteBounds;

		Object::Deserialise(stream);
	}

};