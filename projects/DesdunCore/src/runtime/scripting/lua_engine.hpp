
#include <sol/sol.hpp>
#include <corelib/core.hpp>

namespace DesdunCore
{

	class LuaScriptEngine
	{
	public:
		LuaScriptEngine();


		sol::load_result loadScript(const String& path);

	private:

		sol::state vm = {};

		Dictionary<String, sol::protected_function> cachedScripts = {};

	};

}