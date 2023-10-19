#pragma once

#include "../resource.hpp"


namespace DesdunCore
{

	class ScriptFile : public Resource
	{
	public:

		sol::protected_function& getData();

		static void init();

		static sol::state& getState();
		static List<String>& getLibs();

	protected:
		void load() override;
		void unload() override;

	private:
		sol::protected_function data = {};

		static List<String> environmentLibs;

		static sol::state vm;
	};

}