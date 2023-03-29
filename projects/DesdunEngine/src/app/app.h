#pragma once

#include <GL/glew.h>
#include <glfw3.h>

#include <app/window.h>
#include <app/layer/layer_collection.h>
#include <app/layer/imgui_layer.h>

namespace Desdun
{

	class Application
	{
	public:
		Application();
		~Application();

		virtual void start() { run(); };
		void run();
		void end();

		Window* getPrimaryWindow() const { return gameWindow; };
		float getInterpFraction() const { return stepInterpFrac; };

		LayerCollection gameLayers = {};
		ImGuiLayer* imguiLayer = nullptr;

		float gameSpeed = (1.f / 30.f);
		float timeScale = 1.f;

		static Application* get() { return currentApp; };

	protected:
		void pushInputEvent(Input::Event& event);
		void pushWindowEvent(const Window::Event& event);

	private:
		static Application* currentApp;

		Window* gameWindow = nullptr;
		bool running = false;

		float stepInterpFrac = 0.f;

		friend class Window;
	};

}