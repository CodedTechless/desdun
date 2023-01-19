#pragma once

#include <app/system/window.h>
#include <app/input/event.h>
#include <app/layers/layer_collection.h>

namespace Desdun
{

	class Application
	{
	public:
		Application();
		~Application();

		virtual void Start() { Run(); };
		void Run();
		void End();

		Window* GetPrimaryWindow() const { return GameWindow; };
		float GetInterpolationFraction() const { return StepInterpFrac; };

		LayerCollection GameLayers = {};
		float GameSpeed = (1.f / 30.f);
		float TimeScale = 1.f;

		static Application* GetApplication() { return AppObject; };

	protected:
		void PushInputEvent(const InputEvent& inputEvent);
		void PushWindowEvent(const WindowEvent& windowEvent);

	private:
		static Application* AppObject;

		Window* GameWindow = nullptr;
		bool Running = false;

		float StepInterpFrac = 0.f;

		friend class Window;
	};

}