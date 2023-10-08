#pragma once

/*
an object but also sort of a wrapper class for RenderCamera
*/

#include <desdun_engine/src/runtime/scene/scene.h>
#include <desdun_engine/src/instance/descendants/object.hpp>
#include <desdun_engine/src/instance/descendants/sprite.hpp>

#include <desdun_engine/src/graphics/render/renderer.h>
#include <desdun_engine/src/graphics/render/render_camera.h>

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
