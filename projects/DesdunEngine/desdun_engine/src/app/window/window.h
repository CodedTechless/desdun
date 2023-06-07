#pragma once

/*
interface class for the GLFW window
*/

#include <include/glm/glm.hpp>
#include <include/glew/glew.h>
#include <include/glfw/glfw3.h>
#include <include/desdun_core.hpp>

namespace Desdun
{
	class Window
	{
	public:
		
		Window() = default;
		Window(const std::string& title, Vector2i windowSize);
		~Window();

		struct Event
		{
			Event(Window* window)
			{
				size = window->size;
				isFocused = window->isFocused;
				dpiScale = window->dpiScale;
			}

			Vector2 size = {};
			Vector2 dpiScale = {};
			
			bool isFocused = true;
		};

		void clear();
		void update();

		void setVsyncEnabled(bool Enabled);

		GLFWwindow* getContext() const { return windowObject; };

		Vector2f getContentScale() const { return dpiScale; };
		bool getFocused() const { return isFocused; };
		Vector2i getSize() const { return size; };

	private:
		std::string title = "";
		
		Vector2i size = { 800, 600 };
		Vector2f dpiScale = { 1.f, 1.f };
		bool isFocused = true;

		GLFWwindow* windowObject;

		friend class Input;
		friend struct Event;
	};
}