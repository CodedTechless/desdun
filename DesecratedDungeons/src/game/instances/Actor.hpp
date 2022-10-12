#pragma once

#include <core/instance/base/Instance.h>
#include <gamelib.hpp>

using namespace Desdun;


class Actor : public Instance
{
public:

	Actor(Game* game, const std::string& ID)
		: Instance(game, ID) {};

	void OnAwake()
	{
		tex = CreatePointer<TextureArray>(Vector2(300.f, 300.f), 16);
		tex->SetLayer(0, CreatePointer<Image>("assets/goofy.png"));
	}

	void OnGameStep(const float Delta)
	{

		if (Input::KeyDown(Input::KeyCode::W))
		{
			Pos -= Vector2(0.f, 10.f);
		}

		if (Input::KeyDown(Input::KeyCode::A))
		{
			Pos -= Vector2(10.f, 0.f);
		}

		if (Input::KeyDown(Input::KeyCode::S))
		{
			Pos += Vector2(0.f, 10.f);
		}

		if (Input::KeyDown(Input::KeyCode::D))
		{
			Pos += Vector2(10.f, 0.f);
		}

	}

	void OnFrameUpdate(const float Delta)
	{

		Mat4 Transform = glm::translate(Mat4(1.f), Vector3(Pos, 0.f))
			//			* glm::rotate(Mat4(1.f), glm::radians(0.f), Vector3(0.f, 0.f, 1.f))
			* glm::scale(Mat4(1.f), Vector3(100.f, 100.f, 1.f));

		RenderInterface::Submit({
			Transform, Color4(1.f, 1.f, 1.f, 1.f),
			{
				{ 0.f, 0.f },
				{ 1.f, 0.f },
				{ 1.f, 1.f },
				{ 0.f, 1.f }
			},

			0,
			tex,
			nullptr,

			0
		});
	}

private:

	Vector2 Pos = { 100.f, 100.f };

	ptr<TextureArray> tex = nullptr;

};
