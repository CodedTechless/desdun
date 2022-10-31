#pragma once

#include <gamelib.hpp>

using namespace Desdun;


class Actor : public KinematicBody
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
#if 0

		auto t = GetFrameTransform();



		Mat4 test = glm::translate(Mat4(1.f), Vector3(100.f, 100.f, 0.f))
			* glm::rotate(Mat4(1.f), glm::radians(0.f), Vector3(0.f, 0.f, 1.f))
			* glm::scale(Mat4(1.f), Vector3(1.f, 1.f, 1.f));

		Renderer::Submit({
			test * t * glm::scale(Mat4(1.f), Vector3(32.f, 32.f, 1.f)),
			{ 1.f, 1.f, 1.f, 1.f},
			{
				{ 0.f, 0.f },
				{ 1.f, 1.f }
			},

			GoofyImage,
			nullptr,

			0
			});
#endif // 0

	}

private:

	Image* GoofyImage = nullptr;
	ptr<TextureArray> tex = nullptr;

};
