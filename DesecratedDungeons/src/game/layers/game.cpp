

#include <game_lib.hpp>
#include <uuid.hpp>

#include <game/objects/index.hpp>

#include "game.h"

namespace Desdun
{

	void Game::OnAwake()
	{
		GameScene = new Scene();

		Camera* cam = GameScene->Create<Camera>();
		cam->SetParent(GameScene->getRoot());
		cam->m_RenderCamera.SetOrthoSize({ 800, 600 });

		GameScene->CurrentCamera = cam;

		auto* actor = GameScene->Create<Actor>();
		actor->SetParent(GameScene->getRoot());

		cam->setSubject(actor);

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