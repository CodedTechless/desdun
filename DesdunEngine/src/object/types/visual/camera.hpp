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

		Vector2 targetViewportSize = {};
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

		void onWindowEvent(const Window::Event& event) override
		{
			adjustViewport(event.size);
			/*
			

			Debug::Log(std::to_string(event.size.x) + " " + std::to_string(event.size.y) + " " + std::to_string(aspectRatio));
			Debug::Log(std::to_string(currentSize.x) + " " + std::to_string(currentSize.y));

			setViewportSize();*/
		}

		void adjustViewport(Vector2 realSize)
		{
			if (getScene()->getCurrentCamera() == this)
				Renderer::setViewportSize(realSize);

			if (adjustToAspectRatio)
			{
				renderCamera.SetOrthoSize(Vector2(realSize.x / realSize.y, 1.f) * targetViewportSize.y);
			}
			else
			{
				renderCamera.SetOrthoSize(targetViewportSize);
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
