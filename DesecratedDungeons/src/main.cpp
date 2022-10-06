
#include <game/game.h>

void main()
{
	Desdun::Game* game = new Desdun::Game();

	game->Start();

	delete game;
}