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

		void onGameStep(float delta) override;
		void onFrameUpdate(float delta) override;

	protected:

		Mat4 getProjectionTransform();

		friend class Scene;
	};
}
