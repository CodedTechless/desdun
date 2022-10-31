#pragma once

#include <core/object/object.h>

#include <core/graphics/core/renderer.h>

using namespace Desdun;

class Sprite : public Object
{
public:
	Sprite() = default;

	void OnFrameUpdate(const float delta)
	{
		Mat4 transform = GetFrameTransform() 
			* glm::scale(Mat4(1.f), Vector3(Vector2(SpriteImage->GetSize()), 1.f));

		Renderer::Submit({ transform, Colour, SpriteBounds, SpriteImage, SpriteShader, ZIndex });
	}

	void SetImage(Image* newImage)
	{

	}

	float ZIndex = 0;

	Shader* SpriteShader = nullptr;

	uint SubImages = 1;

	Color4 Colour = { 1.f, 1.f, 1.f, 1.f };

private:

	Image* SpriteImage = nullptr;
	
	ImageBounds SpriteBounds = {
		{ 0.f, 0.f },
		{ 1.f, 1.f }
	};

};