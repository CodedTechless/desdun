#pragma once

#include <game_lib.hpp>

#include <scene/scene.h>

namespace Desdun
{

	class Actor : public Sprite
	{
	public:
		RUNTIME_CLASS_DEF(Actor);

		void OnAwake()
		{

			sprite = GetScene()->Create<Sprite>();
			sprite->Name = "Body";

			sprite->SpriteImage = Resource::Fetch<Image>("assets/textures/skube_idle_right.png");
			sprite->SetParent(this);
			sprite->Position = Vector2(0.f, -16.f);

			SpriteImage = Resource::Fetch<Image>("assets/textures/white.png");

			SaveToFile("assets/models/hello.res");

			Resource::Fetch<Model>("assets/models/hello.res");
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

			Rotation += 90 * Delta;
			sprite->Rotation += 90 * Delta;
		}

		Input::Filter OnInputEvent(InputEvent input, bool processed)
		{
			return Input::Filter::Ignore;
		}

	private:

		Sprite* sprite = nullptr;

	};
}