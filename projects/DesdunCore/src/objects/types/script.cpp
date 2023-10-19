
#include "script.hpp"



namespace DesdunCore
{

	void Script::setScript(const String& path)
	{
		auto* file = Resource::fetch<ScriptFile>(path);

		auto& vm = ScriptFile::getState();
		sol::environment env = { vm, sol::create };

		for (const auto& entry : ScriptFile::getLibs())
		{
			env.set(entry, vm[entry]);
		};

		sol::protected_function data = file->getData();
		
		env.set_on(data);
		sol::protected_function_result res = data.call();

		if (not res.valid())
		{
			sol::error err = res;
			throw Exception(std::format("Failed to instantiate script {}: {}", file->getPath(), err.what()));
		}

		call("onAwake");

		script = env;
	}

	void Script::onDestroyed()
	{
		call("onDestroyed");
	}

	void Script::onGameStep(const float delta)
	{
		call("onGameStep", delta);
	}

	void Script::onFrameUpdate(const float delta)
	{
		call("onFrameUpdate", delta);
	}

	void Script::onInputEvent(Input::Event& input)
	{
		//call("onInputEvent", input);
	}

	void Script::onWindowEvent(const Window::Event& window)
	{
		//call("onWindowEvent", window);
	}

	void Script::serialise(JSONObject& object) const
	{
	}

	void Script::deserialise(const JSONObject& object)
	{
	}
}