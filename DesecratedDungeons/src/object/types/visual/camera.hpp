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

		Mat4 GetProjectionTransform() const
		{
			return m_RenderCamera.GetProjection() * glm::inverse(GetTransform());
		};

		RenderCamera m_RenderCamera{};

	};
}
