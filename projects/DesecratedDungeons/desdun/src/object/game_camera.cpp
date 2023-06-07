
#include "game_camera.hpp"


namespace Desdun
{

	void GameCamera::onAwake()
	{
		interpolate = true;

		Input::Action action = {};
		action.name = "cameraZoom";
		action.type = Input::Type::MouseScrolling;
		action.state = Input::State::Changed;

		Input::registerAction(action);
	}

	void GameCamera::onInputEvent(Input::Event& event)
	{
		if (event.isAction("cameraZoom", Input::State::Changed))
		{
			zoomLevel *= -event.action.delta.y * 0.1f + 1;
		}
	};

	void GameCamera::onGameStep(float delta)
	{
		resize((zoomLevel - getScale()) * zoomAlpha * delta);

		Camera::onGameStep(delta);
	};

}