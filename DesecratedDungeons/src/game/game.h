#pragma once

#include <core/window.h>
#include <core/input/event.h>
#include <core/layers/layer_collection.h>

namespace Desdun
{

	class Game
	{
	public:
		Game();
		~Game();

		void Start();
		void End();

		Window* GetPrimaryWindow() { return GameWindow; };

		static Game* GetInstance() { return GameInstance; };

	protected:
		void PushInputEvent(const InputEvent& inputEvent);
		void PushWindowEvent(const WindowEvent& windowEvent);

	private:
		static Game* GameInstance;

		LayerCollection GameLayers = {};
		Window* GameWindow = nullptr;

		bool Running = false;

		friend class Window;
	};

}