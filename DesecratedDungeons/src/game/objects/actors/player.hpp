#pragma once


#include "actor.hpp"


namespace Desdun
{

	class Player : public Actor
	{
	public:
		RUNTIME_CLASS_DEF(Player);

		Vector2 velocity = { 0.f, 0.f };
		float friction = 1200.f;

		float moveAcceleration = 1200.f;
		float maxVelocity = 180.f;

		void onGameStep(float delta) override
		{
			Vector2 movement = Vector2{
				(float)Input::keyDown(Input::KeyCode::D) - (float)Input::keyDown(Input::KeyCode::A),
				(float)Input::keyDown(Input::KeyCode::S) - (float)Input::keyDown(Input::KeyCode::W)
			};

			Vector2 normalisedMovement = { 0.f, 0.f };
			if (glm::length(movement) > 0.f)
			{
				normalisedMovement = glm::normalize(movement);
			}

			velocity += moveAcceleration * normalisedMovement * delta;

			bool isMoving = glm::length(movement) > 0.f;
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

			//std::cout << normalisedMovement.x << " " << normalisedMovement.y << " " << velocity.x << " " << velocity.y << std::endl;

			Position += velocity * delta;
		}
	};

}