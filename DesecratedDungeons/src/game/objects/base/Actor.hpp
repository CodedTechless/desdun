#pragma once

#include <gamelib.hpp>

#include <core/scene/scene.h>

using namespace Desdun;

class Actor : public KinematicBody
{
public:
	Actor() = default;

	void OnAwake()
	{
		Sprite* sprite = GetScene()->CreateObject<Sprite>();

		sprite->SpriteImage = ResourceService::Fetch<Image>("assets/textures/white.png");
		sprite->SetParent(this);
	}

	void OnGameStep(const float Delta)
	{

		if (Input::KeyDown(Input::KeyCode::W))
		{
			Position -= Vector2(0.f, 10.f);
		}

		if (Input::KeyDown(Input::KeyCode::A))
		{
			Position -= Vector2(10.f, 0.f);
		}

		if (Input::KeyDown(Input::KeyCode::S))
		{
			Position += Vector2(0.f, 10.f);
		}

		if (Input::KeyDown(Input::KeyCode::D))
		{
			Position += Vector2(10.f, 0.f);
		}
	}

};
