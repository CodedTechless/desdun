#pragma once

/*
an object but also sort of a wrapper class for RenderCamera
*/

#include <object/types/object.h>
#include <graphics/render_camera.h>

using namespace Desdun;

namespace Desdun
{
	class Camera : public Object
	{
	public:
		RUNTIME_CLASS_DEF(Camera);

		Camera() = default;

		void OnFrameUpdate(float delta)
		{
			if (subject)
			{
				Vector2 position = subject->Position - (m_RenderCamera.GetOrthoSize() / 2.f);

				Position += (position - Position) / alpha;
			}
		}

		void setSubject(Object* object, bool snap = true)
		{
			subject = object;

			if (snap)
			{
				Position = object->Position;
			}
		}

		Mat4 GetProjectionTransform() const
		{
			return m_RenderCamera.GetProjection() * glm::inverse(GetTransform());
		};

		float alpha = 5.f;
		RenderCamera m_RenderCamera{};

	private:

		Object* subject = nullptr;

	};
}
