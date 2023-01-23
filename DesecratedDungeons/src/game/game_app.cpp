
#include <app/runtime.h>
#include <game/objects/index.hpp>

#include "game_app.hpp"

namespace Desdun
{

	void DesecratedDungeons::start()
	{
		Runtime::Add<GameCamera>("GameCamera", Runtime::Get<Camera>());
		Runtime::Add<Actor>("Actor", Runtime::Get<DynamicBody>());
		{
			Runtime::Add<Player>("Player", Runtime::Get<Actor>());
		}

		Layer* newLayer = new Game();
		gameLayers.PushLayer(newLayer);

		run();

	};

}