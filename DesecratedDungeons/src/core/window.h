#pragma once

#include <dependencies/glm/glm.hpp>

#include <GL/glew.h>
#include <glfw3.h>

namespace Desdun
{
	class Window
	{
	public:
		Window(const char AppTitle[], glm::vec2 Size);
		~Window();

		void Clear();
		void SetVsyncEnabled(bool Enabled);

		void Update();

		GLFWwindow* GetContext() { return WindowObject; };

		bool IsFocused = true;
		glm::vec2 Size;

	private:
		GLFWwindow* WindowObject;
	};
}