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

		Camera() = default;

		void onGameStep(float delta) override
		{
			if (subject)
			{
				Vector2 position = subject->Position - (renderCamera.GetOrthoSize() / 2.f);

				if (smoothFollow)
					Position += (position - Position) * alpha * delta;
				else
					Position = position;
			}
		}

		void onWindowEvent(const Window::Event& event) override
		{
			Renderer::setViewportSize(event.size);

			if (adjustToAspectRatio)
			{
				renderCamera.SetOrthoSize(Vector2(event.size.x / event.size.y, 1.f) * targetViewportSize.y);
			}
			else
			{
				renderCamera.SetOrthoSize(targetViewportSize);
			}
			/*
			

			Debug::Log(std::to_string(event.size.x) + " " + std::to_string(event.size.y) + " " + std::to_string(aspectRatio));
			Debug::Log(std::to_string(currentSize.x) + " " + std::to_string(currentSize.y));

			setViewportSize();*/
		}

		void setSubject(Object* object, bool snap = true)
		{
			subject = object;

			if (snap)
			{
				Position = object->Position;
			}
		}
		
		Mat4 getProjectionTransform() const
		{
			return renderCamera.GetProjection() * glm::inverse(GetInterpTransform());
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
