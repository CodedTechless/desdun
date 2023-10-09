

/*
ENTRY POINT BAYBEEEEEE

BEEEEEG YOSHI
*/

#include <src/app/desdun_app.hpp>
#include <windows.h>

using namespace Desdun;

int main()
{
	DesecratedDungeons* game = nullptr;

	try
	{
		game = new DesecratedDungeons();
		game->init();
	}
	catch (std::runtime_error err)
	{
		MessageBoxA(nullptr, ("An uncaught exception occurred!\n" + std::string(err.what())).c_str(), "Exception", MB_OK);
	}

	delete game;
	return 0;
}