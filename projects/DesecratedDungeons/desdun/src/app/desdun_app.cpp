

#include <desdun/src/instance/index.hpp>

#include <desdun/src/game/item/container.hpp>
#include <desdun/src/game/item/item_slot.hpp>

#include <desdun/src/app/layer/game.hpp>
#include <desdun/src/app/desdun_app.hpp>

namespace Desdun
{

	DesecratedDungeons::DesecratedDungeons()
	{
		Debug::Log("initialising game objects...", "Desdun");

		{
			Runtime::add<GameCamera>({ "GameCamera", Runtime::get<Camera>() });
			Runtime::add<Actor>({ "Actor", Runtime::get<WorldObject>() });
			{
				Runtime::add<Player>({ "Player", Runtime::get<Actor>() });
			}

			Runtime::add<Container>({ "Container" });
			Runtime::add<ItemSlot>({ "ItemSlot" });
		}
	}

	void DesecratedDungeons::init()
	{
		Application::init();

		Layer* newLayer = new Game();
		gameLayers.PushLayer(newLayer);

		start();
	};

}