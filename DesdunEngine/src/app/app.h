#pragma once

#include <GL/glew.h>
#include <glfw3.h>

#include <app/window.h>
#include <app/layers/layer_collection.h>
#include <app/debug/imgui_layer.h>

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
		ImGuiLayer* imguiLayer = nullptr;

		float GameSpeed = (1.f / 30.f);
		float TimeScale = 1.f;

		static Application* GetApplication() { return AppObject; };

	protected:
		void pushInputEvent(Input::Event& event);
		void pushWindowEvent(const Window::Event& event);

	private:
		static Application* AppObject;

		Window* GameWindow = nullptr;
		bool Running = false;

		float StepInterpFrac = 0.f;

		friend class Window;
	};

}