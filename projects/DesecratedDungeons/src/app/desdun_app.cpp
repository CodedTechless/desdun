
#include <src/app/layer/game.hpp>
#include <src/app/desdun_app.hpp>

namespace Desdun
{

	void DesecratedDungeons::init()
	{
		Application::init();

		Layer* newLayer = new Game();
		gameLayers.PushLayer(newLayer);

		start();
	};

}