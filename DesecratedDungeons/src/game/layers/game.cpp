

#include <game_lib.hpp>
#include <uuid.hpp>

#include <game/objects/index.hpp>

#include "game.h"

namespace Desdun
{

	void Game::onAwake()
	{
		gameScene = new Scene();

		auto* camera = gameScene->create<GameCamera>();
		camera->targetViewportSize = { 800, 600 };
		camera->alpha = 15.f;
		camera->setParent(gameScene->getRoot());

		gameScene->currentCamera = camera;

		auto* actor = gameScene->create<Player>();
		actor->setParent(gameScene->getRoot());

		camera->setSubject(actor);

		auto* imagetest = gameScene->create<Sprite>();
		imagetest->image = Resource::fetch<Image>("assets/textures/stone_brick_floor.png");
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