

#include <gamelib.hpp>

#include "game.h"

namespace Desdun
{

	void Game::OnAwake()
	{
		Debug::Log("beep!");

		ptr<Image> image = CreatePointer<Image>("assets/goofy.png");

		GoofyAhh = CreatePointer<TextureArray>(Vector2(300.f,  300.f), 16);
		GoofyAhh->SetLayer(0, image);
	}

	void Game::OnFrameUpdate(const float Delta)
	{
		Mat4 Transform = glm::translate(Mat4(1.f), Vector3(100.f, 100.f, 0.f))
//			* glm::rotate(Mat4(1.f), glm::radians(0.f), Vector3(0.f, 0.f, 1.f))
			* glm::scale(Mat4(1.f), Vector3(100.f, 100.f, 1.f));
		
		RenderCamera cam = {};
		cam.SetOrthoSize(Vector2(800, 600));

		RenderInterface::BeginScene(cam);

		RenderInterface::Submit({
			Transform, Color4(1.f, 1.f, 1.f, 1.f),
			{
				{ 0.f, 0.f },
				{ 1.f, 0.f },
				{ 1.f, 1.f },
				{ 0.f, 1.f }
			},

			0,
			GoofyAhh,
			nullptr,

			0
		});

		RenderInterface::EndScene();

	}

	void Game::OnGameStep(const float Delta)
	{

	}

	Input::Filter Game::OnInputEvent(InputEvent InputObject, bool Processed)
	{

		return Input::Filter::Ignore;
	}

	void Game::OnWindowEvent(WindowEvent WindowObject)
	{

	}
}