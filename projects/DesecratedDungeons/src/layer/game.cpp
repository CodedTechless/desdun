

#include <game_lib.hpp>
#include <uuid.hpp>

#include <src/object/index.hpp>

#include "game.h"

namespace Desdun
{

	void Game::onAwake()
	{
		Debug::Log("Initialising the game...", "Game");

		

		{
			Debug::Log("Registering classes to runtime...", "Game");

			Runtime::registerClass<GameCamera>("GameCamera", Runtime::Get<Camera>());
			Runtime::registerClass<Actor>("Actor", Runtime::Get<DynamicBody>());
			{
				Runtime::registerClass<Player>("Player", Runtime::Get<Actor>());
			}
		}

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

			auto* actor = gameScene->create<Player>();
			actor->setParent(gameScene->getRoot());

			camera->offset = { 0.f, -16.f };
			camera->subject = actor;

			auto* imagetest = gameScene->create<Sprite>();
			imagetest->image = Resource::fetch<Image>("assets/textures/stone_brick_floor.png");
			imagetest->tiles = { 10.f, 10.f };
			imagetest->scale = { 10.f, 10.f };
			imagetest->setParent(gameScene->getRoot());
		}

		{
			Debug::Log("Registering items...", "Game");

			items.emplace("test_item", []() -> Item* { return new Item(); });
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