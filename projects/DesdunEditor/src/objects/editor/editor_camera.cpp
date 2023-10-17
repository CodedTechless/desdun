
#include "editor_camera.hpp"

namespace DesdunEditor
{

	void EditorCamera2D::onAwake()
	{
		Camera2D::onAwake();

		Input::Action action = {};
		action.name = "cameraZoom";
		action.type = Input::Type::MouseScrolling;
		action.state = Input::State::Changed;

		Input::registerAction(action);
	}

	void EditorCamera2D::onInputEvent(Input::Event& event)
	{
		if (event.isAction("cameraZoom", Input::State::Changed))
		{
			zoomLevel *= -event.action.delta.y * 0.1f + 1;
		}
	};

}