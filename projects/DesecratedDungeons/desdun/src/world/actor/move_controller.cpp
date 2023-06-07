#include "move_controller.hpp"

namespace Desdun
{
	void MoveController::step(float delta)
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

		object->translate(velocity * delta);
		moveVector *= 0.f;
	}

	void MoveController::applyInput(Vector2 input)
	{
		moveVector = input;
	}

}

