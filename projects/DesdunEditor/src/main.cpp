

/*
ENTRY POINT BAYBEEEEEE

BEEEEEG YOSHI
*/

#include <app/editor_app.hpp>
#include <windows.h>

using namespace DesdunEditor;

int main()
{
	DesdunEditorApp* app = nullptr;

	try
	{
		app = new DesdunEditorApp();
		app->init();
	}
	catch (std::runtime_error err)
	{
		MessageBoxA(nullptr, ("An uncaught exception occurred!\n" + std::string(err.what())).c_str(), "Exception", MB_OK);
	}

	delete app;
	return 0;
}