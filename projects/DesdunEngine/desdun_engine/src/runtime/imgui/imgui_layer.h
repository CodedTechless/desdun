#pragma once

#include <desdun_engine/src/runtime/layer/layer.h>

namespace Desdun
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