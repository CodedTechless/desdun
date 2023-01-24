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

		Vector2 targetViewportSize = { 800.f, 600.f };
		bool adjustToAspectRatio = true;

		Vector2 trackingPosition = {};

		void onAwake() override
		{
			trackingPosition = position;
		}

		void onGameStep(float delta) override
		{
			if (subject)
			{
				if (smoothFollow)
					trackingPosition += (subject->position - trackingPosition) * alpha * delta;
				else
					trackingPosition = subject->position;

				position = trackingPosition - (renderCamera.GetOrthoSize() * 0.5f);
			}
		}

		void onFrameUpdate(float delta) override
		{
			Window* window = Application::get()->getPrimaryWindow();
			Vector2 windowSize = window->getSize();

			if (getScene()->currentCamera == this)
			{
				Renderer::setViewportSize(windowSize * window->getContentScale());
			}

			if (adjustToAspectRatio)
			{
				Debug::Log(std::to_string(getInterpScale().x));
				renderCamera.SetOrthoSize(Vector2(windowSize.x / windowSize.y, 1.f) * targetViewportSize.y * getInterpScale());
			}
			else
			{
				renderCamera.SetOrthoSize(targetViewportSize * getInterpScale());
			}
		}

		void setSubject(Object* object, bool snap = true)
		{
			subject = object;

			if (snap)
				trackingPosition = subject->position;
		}
		
		Mat4 getProjectionTransform() const
		{
			return renderCamera.GetProjection() * glm::inverse(getInterpTransform());
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
