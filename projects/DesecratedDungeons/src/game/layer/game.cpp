

#include <game_lib.hpp>

#include <game/object/game_camera.hpp>
#include <game/object/actor/player.hpp>

#include "game.h"

namespace Desdun
{

	void Game::onAwake()
	{

		{
			Debug::Log("Setting up the scene...", "Game");

			gameScene = new Scene();
			explorer.setContextScene(gameScene);

			Application::get()->getPrimaryWindow()->setVsyncEnabled(true);

			auto* camera = gameScene->create<GameCamera>();
			camera->targetViewportSize = { 800, 600 };
			camera->alpha = 15.f;
			camera->setParent(gameScene->getRoot());

			gameScene->currentCamera = camera;

#if 0
			auto* actor = gameScene->create<Player>();
			actor->setParent(gameScene->getRoot());
#endif

			auto* playerPrefab = Resource::fetch<Model>("models:player.json");
			auto* actor = (WorldObject*)gameScene->instance(playerPrefab);

			camera->offset = { 0.f, -16.f };
			camera->subject = actor;

			auto* imagetest = gameScene->create<Sprite>();
			imagetest->image = Resource::fetch<Image>("textures:dev/stone_brick_floor.png");
			imagetest->tiles = { 10.f, 10.f };
			imagetest->setScale({ 10.f, 10.f });
			imagetest->setParent(gameScene->getRoot());
		}

		{
			Debug::Log("Registering items...", "Game");

			items.emplace("test_item", []() -> Item* { return new Item(); });

			Debug::Log(std::format("Loaded {} items", items.size()), "Game");
		}

		Debug::Log("Initialised", "Game");
	}

	void Game::onFrameUpdate(const float delta)
	{
		gameScene->onFrameUpdate(delta);
		explorer.onImGuiRender();
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