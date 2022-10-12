
#include <app/core.h>

int main()
{
	Desdun::Application* game = new Desdun::Application();
	game->Start();

	delete game;
	return 0;
}