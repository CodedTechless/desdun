

#include "script.hpp"

#include <app/app.hpp>

namespace DesdunCore
{
	void Script::load()
	{
		auto engine = Application::get()->getScriptEngine();

		sol::load_result result = engine->loadScript(getPath());
	}

	void Script::unload()
	{
	}

}
