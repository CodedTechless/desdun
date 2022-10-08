#pragma once

#include <core/layers/layer.h>
#include <core/input/input.h>
#include <core/input/event.h>

namespace Desdun
{

	class GameLayer : public Layer
	{
	public:
		GameLayer() = default;
		GameLayer(const std::string& Name)
			: Layer(Name) {};

		void OnAwake();

		void OnFrameUpdate(const float Delta);
		void OnGameStep(const float Delta);

		Input::Filter OnInputEvent(InputEvent InputObject, bool Processed);
		void OnWindowEvent(WindowEvent windowEvent);

	private:

	};

}