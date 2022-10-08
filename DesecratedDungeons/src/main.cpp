
#include <game/core.h>

int main()
{
	Desdun::Game* game = new Desdun::Game();
	game->Start();

	delete game;
	return 0;
}