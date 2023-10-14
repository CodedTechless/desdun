#pragma once

#include <runtime/layer/layer.hpp>

namespace DesdunCore
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const String& configName = "imgui.ini");
		
		bool absorbInputs = true;

		void begin();
		void end();
		
		void onAwake() override;
		void onDestroyed() override;
		void onFrameUpdate(float delta) override;
		void onInputEvent(Input::Event& inputEvent) override;

	private:

		float time = 0.f;
		float frames = 0.f;

		float lastFrameCount = 0.f;

		String configPath = "imgui.ini";
	};


}