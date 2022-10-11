#pragma once


#include <app/window.h>
#include <app/input/event.h>
#include <app/layers/layer_collection.h>

namespace Desdun
{

	class Application
	{
	public:
		Application();
		~Application();

		void Start();
		void End();

		Window* GetPrimaryWindow() { return GameWindow; };

		LayerCollection GameLayers = {};

		static Application* GetApplication() { return AppInstance; };

	protected:
		void PushInputEvent(const InputEvent& inputEvent);
		void PushWindowEvent(const WindowEvent& windowEvent);

	private:
		static Application* AppInstance;

		Window* GameWindow = nullptr;
		bool Running = false;

		friend class Window;
	};

}