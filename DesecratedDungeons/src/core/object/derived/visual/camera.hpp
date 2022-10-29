#pragma once

/*
an object but also sort of a wrapper class for RenderCamera
*/

#include <core/object/object.h>
#include <core/graphics/core/render_camera.h>

using namespace Desdun;


class Camera : public Object
{
public:

	Camera() = default;

	Mat4 GetProjectionTransform() const 
	{ 
		return m_RenderCamera.GetProjection() * glm::inverse(GetTransform());
	};

	RenderCamera m_RenderCamera {};

};

