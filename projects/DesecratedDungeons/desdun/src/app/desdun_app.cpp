

#include <desdun/src/instance/index.hpp>

#include <desdun/src/game/item/container.hpp>
#include <desdun/src/game/item/item_slot.hpp>

#include <desdun/src/app/layer/game.h>
#include <desdun/src/app/desdun_app.hpp>

namespace Desdun
{

	void DesecratedDungeons::start()
	{
		Application::start();

		Debug::Log("Initialising the game...", "Game");

		{
			Debug::Log("Registering classes to runtime...", "Game");

			Runtime::add<GameCamera>({ "GameCamera", Runtime::get<Camera>() });
			Runtime::add<Actor>({ "Actor", Runtime::get<WorldObject>() });
			{
				Runtime::add<Player>({ "Player", Runtime::get<Actor>() });
			}

			Runtime::add<Container>({ "Container" });
			Runtime::add<ItemSlot>({ "ItemSlot" });
		}

		Layer* newLayer = new Game();
		gameLayers.PushLayer(newLayer);

		run();
	};

}