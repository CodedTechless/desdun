
#include "camera.hpp"

namespace DesdunCore
{

	void Camera2D::onAwake()
	{
		interpolate = true;

		Input::Action action = {};
		action.name = "cameraZoom";
		action.type = Input::Type::MouseScrolling;
		action.state = Input::State::Changed;

		Input::registerAction(action);
	}

	void Camera2D::onInputEvent(Input::Event& event)
	{
		if (event.isAction("cameraZoom", Input::State::Changed))
		{
			zoomLevel *= -event.action.delta.y * 0.1f + 1;
		}
	};

	void Camera2D::onGameStep(float delta)
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

		if (getScene()->currentCamera == this)
		{
			Vector2f windowSize = Application::get()->getPrimaryWindow()->getSize();
			Vector2f orthoSize = renderCamera.getOrthoSize();

			Vector2f cameraPos = getPosition();
			Vector2f mouseRatio = (Input::getMousePosition() / windowSize) - 0.5f;
			mousePos = cameraPos + orthoSize * mouseRatio * getScale();
		}
	}

	void Camera2D::onFrameUpdate(float delta)
	{
		auto* app = Application::get();

		Vector2 viewportSize = {};

		if (viewport == nullptr)
		{
			Window* window = app->getPrimaryWindow();
			Vector2 windowSize = window->getSize();
		}
		else
		{
			viewportSize = viewport->GetSpecification().Size;
		}

		if (getScene()->currentCamera == this)
		{
			app->getRenderer()->setViewportSize(viewportSize);
		}

		if (adjustToAspectRatio)
		{
			renderCamera.setOrthoSize(Vector2(viewportSize.x / viewportSize.y, 1.f) * targetViewportSize.y * getLocalInterpScale());
		}
		else
		{
			renderCamera.setOrthoSize(targetViewportSize * getLocalInterpScale());
		}
	}

	Mat4 Camera2D::getProjectionTransform()
	{
		return renderCamera.GetProjection() 
			* glm::inverse(
				glm::translate(getRenderTransform(), 
				{ renderCamera.getOrthoSize() * -0.5f, 0.f })
			);
	}

	Vector2 Camera2D::getMouseInWorld() const
	{
		return mousePos;
	}

}