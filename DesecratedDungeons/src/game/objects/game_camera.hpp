#pragma once

#include <object/types/visual/camera.hpp>

namespace Desdun
{

	class GameCamera : public Camera
	{
	public:
		RUNTIME_CLASS_DEF(GameCamera);

		float zoomLevel = 1.f;
		float zoomAlpha = 25.f;

		void onAwake() override
		{
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
				zoomLevel *= -event.action.delta.y * 0.1 + 1;
				Debug::Log(std::to_string(zoomLevel));
			}
		};

		void onGameStep(float delta)
		{
			absoluteZoomLevel += (zoomLevel - absoluteZoomLevel) / zoomAlpha;



			Camera::onGameStep(delta);
		}

	private:

		float absoluteZoomLevel = 1.f;

	};

}