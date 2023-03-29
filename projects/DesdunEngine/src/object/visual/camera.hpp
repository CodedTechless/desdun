#pragma once

/*
an object but also sort of a wrapper class for RenderCamera
*/

#include <scene/scene.h>
#include <object/object.h>
#include <object/visual/sprite.hpp>

#include <graphics/render_camera.h>
#include <graphics/renderer.h>

namespace Desdun
{
	class Camera : public WorldObject
	{
	public:
		serialisable(Camera);

		float alpha = 0.25f;

		bool smoothFollow = true;
		bool adjustToAspectRatio = true;
		
		Vector2 targetViewportSize = { 800.f, 600.f };
		Vector2 offset = { 0.f, 0.f };

		RenderCamera renderCamera = {};
		WorldObject* subject = nullptr;

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
				renderCamera.setOrthoSize(Vector2(windowSize.x / windowSize.y, 1.f) * targetViewportSize.y * getInterpScale());
			}
			else
			{
				renderCamera.setOrthoSize(targetViewportSize * getInterpScale());
			}
		}
		
		Mat4 getProjectionTransform() const
		{
			return renderCamera.GetProjection() * glm::inverse(glm::translate(getInterpTransform(), { renderCamera.getOrthoSize() * -0.5f, 0.f }));
		};

	};
}
