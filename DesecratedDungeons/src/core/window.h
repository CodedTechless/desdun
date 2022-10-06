#pragma once

#include <dependencies/glm/glm.hpp>
#include <libraries.hpp>

#include <glfw3.h>
#include <GL/glew.h>

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

		inline GLFWwindow* GetContext() const { return aWindow; };

		bool IsFocused = true;
		glm::vec2 Size;

	private:
		GLFWwindow* aWindow;
	};
}