

#include <corelibraries.hpp>

#include "game.h"

namespace Desdun
{

	void GameLayer::OnAwake()
	{
		Debug::Log("beep!");

		ptr<Image> image = CreatePointer<Image>("assets/goofy.png");

		GoofyAhh = CreatePointer<TextureArray>(Vector2(300,  300), 16);
		GoofyAhh->SetLayer(0, image);
	}

	void GameLayer::OnFrameUpdate(const float Delta)
	{
		Mat4 Transform = glm::translate(Mat4(1.f), Vector3(100, 100, 0))
			* glm::rotate(Mat4(1.f), glm::radians(0.f), Vector3(0.f, 0.f, 1.f))
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

	void GameLayer::OnGameStep(const float Delta)
	{

	}

	Input::Filter GameLayer::OnInputEvent(InputEvent InputObject, bool Processed)
	{

		return Input::Filter::Ignore;
	}

	void GameLayer::OnWindowEvent(WindowEvent WindowObject)
	{

	}
}