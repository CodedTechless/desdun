#pragma once

#include <app/input/input.h>

#include <libraries.hpp>

namespace Desdun
{

	struct InputEvent
	{
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

}