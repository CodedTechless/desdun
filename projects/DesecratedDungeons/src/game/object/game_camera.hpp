#pragma once

#include <object/visual/camera.hpp>

namespace Desdun
{

	class GameCamera : public Camera
	{
	public:
		
		float zoomLevel = 1.f;
		float zoomAlpha = 15.f;

		void onAwake() override;
		void onInputEvent(Input::Event& event) override;
		void onGameStep(float delta) override;

	};

}