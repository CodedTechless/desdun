#pragma once

#include <object/object.h>

#include <graphics/renderer.h>

using namespace Desdun;

class Sprite : public Object
{
public:

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

};