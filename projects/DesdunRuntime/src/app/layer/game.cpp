
#include "game.hpp"

namespace DesdunCore
{

	void Game::onAwake()
	{
		gameScene = new Scene();

		Application::get()->getPrimaryWindow()->setVsyncEnabled(false);

		auto* camera = gameScene->create<Camera2D>();
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

	void Game::onFrameUpdate(const float delta)
	{
		gameScene->onFrameUpdate(delta);
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