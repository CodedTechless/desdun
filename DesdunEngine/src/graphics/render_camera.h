#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include <core_lib.hpp>

namespace Desdun
{

	class RenderCamera
	{
	public:
		RenderCamera() = default;

		void SetOrthoSize(Vector2 Size)
		{
			m_OrthoSize = Size;
			CalculateProjection();
		}

		void SetOrthoZPlane(Vector2 ZPlane)
		{
			m_OrthoZPlane = ZPlane;
			CalculateProjection();
		}

		Vector2 GetOrthoSize() const { return m_OrthoSize; };
		Vector2 GetOrthoZPlane() const { return m_OrthoZPlane; };

		Mat4f GetProjection() const { return m_Projection; };

	private:

		void CalculateProjection()
		{
			m_Projection = glm::ortho(0.f, m_OrthoSize.x, m_OrthoSize.y, 0.f, m_OrthoZPlane.x, m_OrthoZPlane.y);
		}

		Mat4f m_Projection = {};
		
		Vector2f m_OrthoSize = { 800.f, 600.f };
		Vector2f m_OrthoZPlane = { -100.f, 100.f };
	};

}