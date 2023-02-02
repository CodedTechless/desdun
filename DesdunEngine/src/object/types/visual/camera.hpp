#pragma once

/*
an object but also sort of a wrapper class for RenderCamera
*/

#include <scene/scene.h>
#include <object/types/object.h>

#include <graphics/render_camera.h>
#include <graphics/renderer.h>

namespace Desdun
{
	class Camera : public Object
	{
	public:
		RUNTIME_CLASS_DEF(Camera);

		float alpha = 0.25f;

		bool smoothFollow = true;
		bool adjustToAspectRatio = true;
		
		Vector2 targetViewportSize = { 800.f, 600.f };
		Vector2 offset = { 0.f, 0.f };

		void onGameStep(float delta) override
		{
			if (subject)
			{
				Vector2 finalPosition = subject->position + offset;

				if (smoothFollow)
					position += (finalPosition - position) * alpha * delta;
				else
					position = finalPosition;
			}

		}

		void onFrameUpdate(float delta) override
		{
			Window* window = Application::get()->getPrimaryWindow();
			Vector2 windowSize = window->getSize();

			if (getScene()->currentCamera == this)
			{
				Renderer::setViewportSize(windowSize);
			}

			if (adjustToAspectRatio)
			{
				renderCamera.SetOrthoSize(Vector2(windowSize.x / windowSize.y, 1.f) * targetViewportSize.y * getInterpScale());
			}
			else
			{
				renderCamera.SetOrthoSize(targetViewportSize * getInterpScale());
			}
		}

		void setSubject(Object* object, Vector2 objectOffset = {}, bool snap = true)
		{
			subject = object;
			offset = objectOffset;

			if (snap)
				position = subject->position;
		}
		
		Mat4 getProjectionTransform() const
		{
			return renderCamera.GetProjection() * glm::inverse(glm::translate(getInterpTransform(), { renderCamera.GetOrthoSize() * -0.5f, 0.f }));
		};

		RenderCamera& getRenderCamera()
		{
			return renderCamera;
		}

	private:

		RenderCamera renderCamera = {};
		Object* subject = nullptr;

	};
}
