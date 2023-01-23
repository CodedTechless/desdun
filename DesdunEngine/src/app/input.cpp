
/*
	class InputEvent
	{
	public:
		Input::Type InputType = Input::Type::None;
		Input::State InputState = Input::State::None;

		Input::KeyCode KeyCode = Input::KeyCode::None;
		Input::MouseCode MouseCode = Input::MouseCode::None;

		glm::vec3 Position = {};
		glm::vec3 Delta = {};
	};


	struct WindowEvent
	{
		glm::vec2 Size = {};
		bool Focused = true;
	};
*/

#include <app/app.h>

#include "input.h"

namespace Desdun
{
	std::unordered_map<std::string, Input::Action> Input::registeredActions = {};

	bool Input::keyDown(const Input::KeyCode Key)
	{
		auto Window = Application::GetApplication()->GetPrimaryWindow()->getContext();
		auto State = glfwGetKey(Window, (int)Key);

		return State == GLFW_PRESS || State == GLFW_REPEAT;
	}
	
	bool Input::mouseButtonDown(const Input::MouseCode Button)
	{
		auto Window = Application::GetApplication()->GetPrimaryWindow()->getContext();
		auto State = glfwGetMouseButton(Window, (int)Button);

		return State == GLFW_PRESS;
	}

	glm::vec2 Input::getMousePosition() 
	{
		auto* Window = Application::GetApplication()->GetPrimaryWindow();
		auto* Context = Window->getContext();
		Vector2 Size = Window->getSize();

		double X, Y;
		glfwGetCursorPos(Context, &X, &Y);

		return { 
			std::min((float)Size.x, std::max(0.f, (float)X)) , 
			std::min((float)Size.y, std::max(0.f, (float)Y))
		};
	}
}
