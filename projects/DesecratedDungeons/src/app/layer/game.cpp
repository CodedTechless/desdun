
#include "game.hpp"

namespace Desdun
{

	void Game::onAwake()
	{

		{
			Debug::Log("Setting up the scene...", "Game");

			gameScene = new Scene();

			Application::get()->getPrimaryWindow()->setVsyncEnabled(false);

			auto* camera = gameScene->create<Camera>();
			camera->targetViewportSize = { 800, 600 };
			camera->alpha = 15.f;
			camera->setParent(gameScene->getRoot());

			gameScene->currentCamera = camera;

			auto* imagetest = gameScene->create<Sprite>();
			imagetest->image = Resource::fetch<Image>("textures:dev/stone_brick_floor.png");
			imagetest->tiles = { 10.f, 10.f };
			imagetest->setScale({ 10.f, 10.f });
			imagetest->setParent(gameScene->getRoot());
		}

#if 0
		{
			Debug::Log("Initialising tools");
			explorer = new SceneExplorer();
			explorer->setContextScene(gameScene);

		}
#endif

		Debug::Log("Initialised", "Game");
	}

	void Game::onFrameUpdate(const float delta)
	{
		gameScene->onFrameUpdate(delta);

#if 0
		explorer->onImGuiRender();
#endif
	}

	void Game::onGameStep(const float Delta)
	{
		gameScene->onGameStep(Delta);
	}

	void Game::onInputEvent(Input::Event& event)
	{
		return gameScene->onInputEvent(event);
	}

	void Game::onWindowEvent(const Window::Event& event)
	{
		gameScene->onWindowEvent(event);
	}
}