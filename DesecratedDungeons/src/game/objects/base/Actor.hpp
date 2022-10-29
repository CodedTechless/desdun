#pragma once

#include <gamelib.hpp>

using namespace Desdun;


class Actor : public KinematicObject
{
public:
	Actor() = default;

	void OnAwake()
	{
		GoofyImage = ResourceService::Fetch<Image>("assets/goofy.png");

		tex = CreatePointer<TextureArray>(Vector2(300.f, 300.f), 16);
		GoofyImage->Allocate(tex, 0);
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

		Renderer::Submit({
			GetFrameTransform() * glm::scale(Mat4(1.f), Vector3(100.f, 100.f, 1.f)),
			{ 1.f, 1.f, 1.f, 1.f},
			{
				{ 0.f, 0.f },
				{ 1.f, 0.f },
				{ 1.f, 1.f },
				{ 0.f, 1.f }
			},

			GoofyImage,
			nullptr,

			0
		});

	}

private:

	Image* GoofyImage = nullptr;
	ptr<TextureArray> tex = nullptr;

};
