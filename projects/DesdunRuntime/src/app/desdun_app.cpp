
#include <app/layer/game.hpp>
#include <app/desdun_app.hpp>

namespace DesdunRuntime
{

	void DesdunRuntimeApp::init()
	{
		Application::init();

		Layer* newLayer = new Game();
		gameLayers.pushLayer(newLayer);

		start();
	};

}