
#include <app/runtime/runtime_info.h>
#include <game/objects/index.hpp>

#include "game_app.hpp"

namespace Desdun
{

	void DesecratedDungeons::Start()
	{
		Runtime::Add<Actor>("Actor", Runtime::Get<Sprite>());

		Layer* newLayer = new Game();
		GameLayers.PushLayer(newLayer);

		Run();

	};

}