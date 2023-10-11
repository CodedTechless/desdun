
#include "camera.hpp"

namespace Desdun
{

	void Camera::onAwake()
	{
		interpolate = true;

		Input::Action action = {};
		action.name = "cameraZoom";
		action.type = Input::Type::MouseScrolling;
		action.state = Input::State::Changed;

		Input::registerAction(action);
	}

	void Camera::onInputEvent(Input::Event& event)
	{
		if (event.isAction("cameraZoom", Input::State::Changed))
		{
			zoomLevel *= -event.action.delta.y * 0.1f + 1;
		}
	};

	void Camera::onGameStep(float delta)
	{
		resize((zoomLevel - getScale()) * zoomAlpha * delta);

		if (subject)
		{
			Vector2 finalPosition = subject->getPosition() + offset;

			if (smoothFollow)
				translate((finalPosition - getPosition()) * alpha * delta);
			else
				setPosition(finalPosition);
		}

	}

	void Camera::onFrameUpdate(float delta)
	{
		auto* app = Application::get();
		Window* window = app->getPrimaryWindow();
		Vector2 windowSize = window->getSize();

		if (getScene()->currentCamera == this)
		{
			app->getRenderer()->setViewportSize(windowSize);
		}

		if (adjustToAspectRatio)
		{
			renderCamera.setOrthoSize(Vector2(windowSize.x / windowSize.y, 1.f) * targetViewportSize.y * getLocalInterpScale());
		}
		else
		{
			renderCamera.setOrthoSize(targetViewportSize * getLocalInterpScale());
		}
	}

	Mat4 Camera::getProjectionTransform()
	{
		return renderCamera.GetProjection() 
			* glm::inverse(
				glm::translate(getRenderTransform(), 
				{ renderCamera.getOrthoSize() * -0.5f, 0.f })
			);
	}

}