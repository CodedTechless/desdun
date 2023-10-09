#pragma once

#include <include/glew/glew.h>
#include <include/glfw/glfw3.h>

#include <src/app/window/window.h>
#include <src/runtime/layer/layer_collection.h>
#include <src/runtime/imgui/imgui_layer.h>

#include <src/graphics/render/renderer.h>

namespace Desdun
{

	class Application
	{
	public:

		Application();
		~Application();
		
		LayerCollection gameLayers = {};

		virtual void init();
		void stop();

		Window* getPrimaryWindow() const;
		float getInterpFraction() const;

		Renderer* getRenderer() const;
		static Application* get();

	protected:

		void start();

		void pushInputEvent(Input::Event& event);
		void pushWindowEvent(const Window::Event& event);

	private:

		bool running = false;

		float gameSpeed = (1.f / 30.f);
		float timeScale = 1.f;
		float stepInterpFrac = 0.f;

		Window* gameWindow = nullptr;
		Renderer* renderer = nullptr;
		ImGuiLayer* imguiLayer = nullptr;

		static Application* currentApp;

		friend class Window;
	};

}