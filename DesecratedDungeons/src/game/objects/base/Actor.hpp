#pragma once

#include <core/instance/index.hpp>
#include <gamelib.hpp>

using namespace Desdun;


class Actor : public WorldInstance
{
public:
	Actor() = default;

	void OnAwake()
	{
		auto GoofyImage = ResourceService::Fetch<Image>("assets/goofy.png");

		tex = CreatePointer<TextureArray>(Vector2(300.f, 300.f), 16);
		tex->SetLayer(0, GoofyImage);
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

	void OnFrameUpdate(const float Delta)
	{

		Mat4 Transform = glm::translate(Mat4(1.f), Vector3(Pos, 0.f))
			//			* glm::rotate(Mat4(1.f), glm::radians(0.f), Vector3(0.f, 0.f, 1.f))
			* glm::scale(Mat4(1.f), Vector3(100.f, 100.f, 1.f));

		Renderer::Submit({
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
