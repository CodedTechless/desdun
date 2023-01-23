#pragma once

/*
interface class for the GLFW window
*/

#include <dependencies/glm/glm.hpp>

#include <GL/glew.h>
#include <glfw3.h>

#include <core_lib.hpp>

namespace Desdun
{
	class Window
	{
	public:
		
		Window() = default;
		Window(const std::string& title, Vector2 size);
		~Window();

		struct Event
		{
			glm::vec2 size = {};
			bool focused = true;
		};

		void clear();
		void update();

		void setVsyncEnabled(bool Enabled);

		GLFWwindow* getContext() const { return windowObject; };

		bool getFocused() const { return isFocused; };
		Vector2 getSize() const { return size; };

	private:
		std::string title = "";
		
		Vector2 size = {};
		bool isFocused = true;

		GLFWwindow* windowObject;

		friend class Input;
	};
}