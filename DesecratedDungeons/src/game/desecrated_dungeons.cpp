
#include <app/runtime.h>
#include <src/object/index.hpp>

#include "desecrated_dungeons.hpp"

namespace Desdun
{

	void DesecratedDungeons::start()
	{

		Layer* newLayer = new Game();
		gameLayers.PushLayer(newLayer);

		run();

	};

}