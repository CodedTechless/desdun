

#include <windows.h>

/*
ENTRY POINT BAYBEEEEEE

BEEEEEG YOSHI
*/

#include <game/desecrated_dungeons.hpp>

using namespace Desdun;

int main()
{
	DesecratedDungeons* game = nullptr;

	try
	{
		game = new DesecratedDungeons();
		game->start();
	}
	catch (std::runtime_error err)
	{
		MessageBoxA(nullptr, ("An uncaught exception occurred!\n" + std::string(err.what())).c_str(), "Exception", MB_OK);
	}

	delete game;
	return 0;
}