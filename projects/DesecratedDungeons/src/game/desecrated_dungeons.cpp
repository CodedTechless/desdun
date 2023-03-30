
#include <game/layer/game.h>

#include <game/object/game_camera.hpp>
#include <game/object/actor/actor.hpp>
#include <game/object/actor/player.hpp>

#include <game/world/item/container.hpp>
#include <game/world/item/item_slot.hpp>

#include "desecrated_dungeons.hpp"

namespace Desdun
{

	void DesecratedDungeons::start()
	{
		Debug::Log("Initialising the game...", "Game");

		{
			Debug::Log("Registering classes to runtime...", "Game");

			Runtime::registerClass<GameCamera>("GameCamera", Runtime::get<Camera>());
			Runtime::registerClass<Actor>("Actor", Runtime::get<DynamicBody>());
			{
				Runtime::registerClass<Player>("Player", Runtime::get<Actor>());
			}

			Runtime::registerClass<Container>("Container");
			Runtime::registerClass<ItemSlot>("ItemSlot");
		}

		Layer* newLayer = new Game();
		gameLayers.PushLayer(newLayer);

		run();

	};

}