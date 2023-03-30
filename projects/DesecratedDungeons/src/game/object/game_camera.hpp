#pragma once

#include <object/visual/camera.hpp>

namespace Desdun
{

	class GameCamera : public Camera
	{
	public:
		
		float zoomLevel = 1.f;
		float zoomAlpha = 15.f;

		void onAwake() override
		{
			interpolate = true;

			Input::Action action = {};
			action.name = "cameraZoom";
			action.type = Input::Type::MouseScrolling;
			action.state = Input::State::Changed;

			Input::registerAction(action);
		}
		
		void onInputEvent(Input::Event& event) override
		{
			if (event.isAction("cameraZoom", Input::State::Changed))
			{
				zoomLevel *= -event.action.delta.y * 0.1f + 1;
			}
		};

		void onGameStep(float delta) override
		{
			scale += (zoomLevel - scale) * zoomAlpha * delta;

			Camera::onGameStep(delta);
		};

	};

}