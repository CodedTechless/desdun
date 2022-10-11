#pragma once

#include <app/input/event.h>

#include <libraries.hpp>

namespace Desdun 
{
	class Layer
	{
	public:
		Layer() = default;
		Layer(const std::string& layerName);
		virtual ~Layer() = default;

		virtual void OnAwake() {};
		virtual void OnDestroyed() {};

		virtual void OnFrameUpdate(const float Delta) {};
		virtual void OnGameStep(const float Delta) {};

		virtual Input::Filter OnInputEvent(InputEvent inputEvent, bool Processed) { return Input::Filter::Ignore; };
		virtual void OnWindowEvent(WindowEvent inputEvent) {};

	protected:
		std::string LayerName = "Layer";

	};
}