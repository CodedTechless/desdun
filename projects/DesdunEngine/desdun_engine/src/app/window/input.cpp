
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
		auto Window = Application::get()->getPrimaryWindow()->getContext();
		auto State = glfwGetKey(Window, (int)Key);

		return State == GLFW_PRESS || State == GLFW_REPEAT;
	}
	
	bool Input::mouseButtonDown(const Input::MouseCode Button)
	{
		auto Window = Application::get()->getPrimaryWindow()->getContext();
		auto State = glfwGetMouseButton(Window, (int)Button);

		return State == GLFW_PRESS;
	}

	Vector2f Input::getMousePosition() 
	{
		auto* Window = Application::get()->getPrimaryWindow();
		auto* Context = Window->getContext();
		Vector2f Size = Window->getSize();

		double X, Y;
		glfwGetCursorPos(Context, &X, &Y);

		return { 
			std::clamp((float)X, 0.f, Size.x),
			std::clamp((float)Y, 0.f, Size.y)
		};
	}
}
