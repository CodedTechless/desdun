
#include "camera.hpp"

namespace Desdun
{

	void Camera::onGameStep(float delta)
	{
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
		Window* window = Application::get()->getPrimaryWindow();
		Vector2 windowSize = window->getSize();

		if (getScene()->currentCamera == this)
		{
			Renderer::setViewportSize(windowSize);
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