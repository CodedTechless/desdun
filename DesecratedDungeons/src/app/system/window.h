#pragma once

/*
interface class for the GLFW window
*/

#include <dependencies/glm/glm.hpp>

#include <GL/glew.h>
#include <glfw3.h>

#include <libraries.hpp>

namespace Desdun
{
	class Window
	{
	public:
		Window() = default;
		Window(const std::string& title, Vector2 size);
		~Window();

		void Clear();
		void Update();

		void SetVsyncEnabled(bool Enabled);

		GLFWwindow* GetContext() const { return WindowObject; };

		bool GetFocused() const { return IsFocused; };
		Vector2 GetSize() const { return Size; };

	private:
		std::string Title = "";
		
		Vector2 Size = {};
		bool IsFocused = true;

		GLFWwindow* WindowObject;

		friend class Input;
	};
}