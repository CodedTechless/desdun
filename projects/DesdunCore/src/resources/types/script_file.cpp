

#include "script_file.hpp"

#include <app/app.hpp>

namespace DesdunCore
{



	sol::state ScriptFile::vm = {};

	sol::protected_function& ScriptFile::getData()
	{
		return data;
	}

	void ScriptFile::init()
	{
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
