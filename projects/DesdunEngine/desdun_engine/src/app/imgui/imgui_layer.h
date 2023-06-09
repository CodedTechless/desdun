#pragma once

#include <desdun_engine/src/app/layer/layer.h>

namespace Desdun
{

	class ImGuiLayer : public Layer
	{
	public:
		bool absorbInputs = true;

		ImGuiLayer(const std::string& iniFileName = "imgui.ini")
			: Layer("ImGuiLayer"), iniFileName(iniFileName) {};

		void onAwake() override;
		void onDestroyed() override;

		void onFrameUpdate(float delta) override;

		void begin();
		void end();

	private:

		float lastFrameCount = 0.f;
		float frames = 0.f;

		float time = 0.f;

		std::string iniFileName = "imgui.ini";
	};


}