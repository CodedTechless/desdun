#pragma once

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include <app/window/window.hpp>
#include <runtime/layer/layer_collection.hpp>
#include <runtime/imgui/imgui_layer.hpp>

#include <graphics/render/renderer.hpp>

namespace DesdunCore
{

	class Application
	{
	public:

		Application();
		~Application();
		
		struct Performance
		{
			uint frameRate;
		};

		LayerCollection gameLayers = {};

		virtual void init();
		void stop();

		Window* getPrimaryWindow() const;
		float getInterpFraction() const;

		Renderer* getRenderer() const;
		static Application* get();

		ImGuiLayer* getImGuiLayer() const;

		void showDebug();

	protected:

		void start();

		void pushInputEvent(Input::Event& event);
		void pushWindowEvent(const Window::Event& event);

	private:

		bool running = false;

		float gameSpeed = (1.f / 30.f);
		float timeScale = 1.f;
		float stepInterpFrac = 0.f;

		uint frameRate = 0;
		float frameDelta = 0.f;

		Window* gameWindow = nullptr;
		Renderer* renderer = nullptr;
		ImGuiLayer* imguiLayer = nullptr;

		static Application* currentApp;

		friend class Window;
	};

}