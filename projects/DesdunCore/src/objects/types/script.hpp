#pragma once

#include <resources/types/script_file.hpp>

#include <objects/object.hpp>

namespace DesdunCore
{

	class Script : public Object
	{
	public:
		dd_serialisable(Script);

		template<typename... Args>
		sol::protected_function_result call(const String& name, Args&&... args)
		{
			
		};

		void setScript(const String& path);

		void onDestroyed() override;

		void onGameStep(const float delta) override;
		void onFrameUpdate(const float delta) override;

		void onInputEvent(Input::Event& input) override;
		void onWindowEvent(const Window::Event& window) override;

	private:
		void serialise(JSONObject& object) const override;
		void deserialise(const JSONObject& object) override;

		ScriptFile* resource = nullptr;
		sol::environment script;

	};

}
