#pragma once

#include <desdun_engine/desdun_engine.hpp>


namespace Desdun
{

	/*
		Manages physics movement for any Instance it is provided.
		When a MoveController is given inputs, it will perform
		movements and physics calculations.
	*/
	class MoveController
	{
	public:

		MoveController(WorldObject* owner)
			: object(owner) {};

		Vector2 velocity = { 0.f, 0.f };
		float maxVelocity = 125.f;

		float friction = 2000.f;
		float moveAcceleration = 1800.f;

		void step(float delta);
		void applyInput(Vector2 dir);

	private:

		Vector2 moveVector = { 0.f, 0.f };
		WorldObject* object = nullptr;

	};

}