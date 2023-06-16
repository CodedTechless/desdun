
#include "move_phys.hpp"

// TODO: remove modifiers and turn them into objects

namespace Desdun
{
	void KinematicActor::onGameStep(const float_t delta)
	{

		velocity += moveAcceleration * moveVector * delta;

		bool isMoving = glm::length(moveVector) > 0.f;
		float scalarVelocity = glm::length(velocity);

		if (scalarVelocity > 0.f)
		{
			if (!isMoving)
			{
				scalarVelocity = glm::max(0.f, scalarVelocity - friction * delta);
			}
			else if (scalarVelocity > maxVelocity)
			{
				scalarVelocity = glm::max(maxVelocity, scalarVelocity - friction * delta);
			}

			velocity = glm::normalize(velocity) * scalarVelocity;
		}

		this->translate(velocity * delta);
		moveVector *= 0.f;
	}

	void KinematicActor::move(Vector2 input)
	{
		moveVector = input;
	}

	void KinematicActor::serialise(JSONObject& object) const
	{
		s_export(velocity);
		s_export(maxVelocity);
		s_export(friction);
		s_export(moveAcceleration);

		Actor::serialise(object);
	}

	void KinematicActor::deserialise(const JSONObject& object)
	{
		s_import(velocity);
		s_import(maxVelocity);
		s_import(friction);
		s_import(moveAcceleration);

		Actor::deserialise(object);
	}

}

