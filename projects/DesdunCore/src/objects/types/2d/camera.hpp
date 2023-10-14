#pragma once

/*
an object but also sort of a wrapper class for RenderCamera
*/

#include <runtime/scene/scene.hpp>
#include <objects/types/2d/entity.hpp>
#include <objects/types/2d/sprite.hpp>

#include <graphics/render/renderer.hpp>
#include <graphics/render/render_camera.hpp>

namespace DesdunCore
{
	class Camera2D : public Entity2D
	{
	public:
		serialisable(Camera2D);

		float alpha = 0.25f;

		float zoomLevel = 1.f;
		float zoomAlpha = 15.f;

		bool smoothFollow = true;
		bool adjustToAspectRatio = true;
		
		Vector2 targetViewportSize = { 800.f, 600.f };
		Vector2 offset = { 0.f, 0.f };

		RenderCamera renderCamera = {};
		Entity2D* subject = nullptr;

		void onAwake() override;

		void onInputEvent(Input::Event& event) override;

		void onGameStep(float delta) override;
		void onFrameUpdate(float delta) override;

		Vector2 getMouseInWorld() const;

	protected:

		Vector2f mousePos = { 0.f, 0.f };

		Mat4 getProjectionTransform();

		friend class Scene;
	};
}
