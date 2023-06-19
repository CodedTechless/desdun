#pragma once

#include <desdun_engine/src/app/window/input.h>
#include <desdun_engine/src/app/window/window.h>

#include <desdun_engine/include/desdun_core.hpp>

namespace Desdun 
{
	class Layer
	{
	public:
		Layer() = default;
		Layer(const std::string& layerName);
		virtual ~Layer() = default;

		virtual void onAwake() {};
		virtual void onDestroyed() {};

		virtual void onFrameUpdate(const float Delta) {};
		virtual void onGameStep(const float Delta) {};

		virtual void onInputEvent(Input::Event& inputEvent) {};
		virtual void onWindowEvent(const Window::Event& inputEvent) {};

		const String name() const { return LayerName; };

	protected:

		std::string LayerName = "Layer";

		friend class Application;
	};
}