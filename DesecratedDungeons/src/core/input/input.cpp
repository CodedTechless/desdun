
#include "input.h"

#include <game/core.h>

namespace Desdun
{
	bool Input::KeyDown(const Input::KeyCode Key)
	{
		auto Window = Game::GetInstance()->GetPrimaryWindow()->GetContext();
		auto State = glfwGetKey(Window, (int)Key);

		return State == GLFW_PRESS || State == GLFW_REPEAT;
	}
	
	bool Input::MouseButtonDown(const Input::MouseCode Button)
	{
		auto Window = Game::GetInstance()->GetPrimaryWindow()->GetContext();
		auto State = glfwGetMouseButton(Window, (int)Button);

		return State == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition() 
	{
		Window* Window = Game::GetInstance()->GetPrimaryWindow();
		GLFWwindow* Context = Window->GetContext();
		glm::vec2 Size = Window->Size;

		double X, Y;
		glfwGetCursorPos(Context, &X, &Y);

		return { 
			std::min((float)Size.x, std::max(0.f, (float)X)) , 
			std::min((float)Size.y, std::max(0.f, (float)Y))
		};
	}
}
