#pragma once

#include "actor.hpp"


namespace Desdun
{

	class Player : public Actor
	{
	public:
		RUNTIME_CLASS_DEF(Player);

		Vector2 velocity = { 0.f, 0.f };
		float maxVelocity = 125.f;
		float friction = 2000.f;

		Vector2 faceDirection = { 0.f, 0.f };
		Vector2 moveDirection = { 0.f, 0.f };
		float moveAcceleration = 1800.f;

		void onAwake() override;

		void onInputEvent(Input::Event& event) override;

		void onFrameUpdate(float delta) override;
		void onGameStep(float delta) override;
	};

}