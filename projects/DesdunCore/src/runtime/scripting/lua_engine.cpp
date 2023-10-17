

#include "lua_engine.hpp"

namespace DesdunCore
{

	LuaScriptEngine::LuaScriptEngine()
	{
		vm.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::utf8);



	}

	sol::load_result LuaScriptEngine::loadScript(const String& path)
	{
		return sol::load_result();
	}


}