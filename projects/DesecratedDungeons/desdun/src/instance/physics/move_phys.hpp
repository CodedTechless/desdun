#pragma once

#include <desdun_engine/desdun_engine.hpp>

#include <desdun/src/instance/actor/actor.hpp>

namespace Desdun
{

	/*
		Manages physics movement for any Instance it is provided.
		When a KinematicActor is given inputs, it will perform
		movements and physics calculations.
	*/
	class KinematicActor : public Actor
	{
	public:
		serialisable(KinematicActor);

		Vector2 velocity = { 0.f, 0.f };
		float maxVelocity = 125.f;

		float friction = 2000.f;
		float moveAcceleration = 1800.f;

		void onGameStep(const float_t delta) override;

	protected:

		void move(Vector2 dir);

		void serialise(JSONObject& object) const;
		void deserialise(const JSONObject& object);

	private:

		Vector2 moveVector = { 0.f, 0.f };

	};

}