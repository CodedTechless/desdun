

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
			dd_class_child(GameCamera, Camera);
			dd_class_child(Actor, WorldObject);
			{
				dd_class_child(KinematicActor, Actor);
				{
					dd_class_child(Player, KinematicActor);
				}
			}

			dd_class_child(HumanoidBodyController, WorldObject);
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