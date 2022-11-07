

#include <gamelib.hpp>
#include <uuid.hpp>

#include "game.h"

namespace Desdun
{

	void Game::OnAwake()
	{
		Debug::Log("beep!");

		GameScene = new Scene();

		auto* cam = GameScene->CreateObject<Camera>();
		cam->m_RenderCamera.SetOrthoSize({ 800, 600 });

		GameScene->CurrentCamera = cam;

		GameScene->CreateObject<Actor>();

	}

	void Game::OnFrameUpdate(const float delta)
	{
		GameScene->OnFrameUpdate(delta);
	}

	void Game::OnGameStep(const float Delta)
	{
		GameScene->OnGameStep(Delta);
	}

	Input::Filter Game::OnInputEvent(InputEvent InputObject, bool Processed)
	{
		return GameScene->OnInputEvent(InputObject, Processed);
	}

	void Game::OnWindowEvent(WindowEvent WindowObject)
	{
		GameScene->OnWindowEvent(WindowObject);
	}
}