

#include "script_file.hpp"

#include <app/app.hpp>

namespace DesdunCore
{

	List<String> ScriptFile::environmentLibs = {
		"print", "warn", "error",
		"math", "coroutine", "string",
		"require", "assert", "tostring",
		"tonumber", "pcall",
		"table", "next", "pairs", "ipairs"
	};

	sol::state ScriptFile::vm = {};

	sol::protected_function& ScriptFile::getData()
	{
		return data;
	}

	void ScriptFile::init()
	{
		vm.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::math, sol::lib::table, sol::lib::utf8);
	}

	sol::state& ScriptFile::getState()
	{
		return vm;
	}

	List<String>& ScriptFile::getLibs()
	{
		return environmentLibs;
	}

	void ScriptFile::load()
	{
		sol::load_result result = vm.load_file(path);

		if (not result.valid())
		{
			sol::error err = result;
			throw Exception(std::format("Couldn't load script {}: {}", path, err.what()));
		}

		data = result;
	}

	void ScriptFile::unload()
	{
	}



}
