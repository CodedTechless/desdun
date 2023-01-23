#pragma once


#include <object/types/object.h>

namespace Desdun
{

	class DynamicBody : public Object
	{
	public:
		RUNTIME_CLASS_DEF(DynamicBody);

		Vector2 velocity = { 0.f, 0.f };
		float friction = 200.f;

		DynamicBody()
		{
			// add it to the collision system
		};

		~DynamicBody()
		{
			// remove it from the collision system
		};

		void applyForce(Vector2 magnitude)
		{
			velocity += magnitude;
		}

		void applyForce(float magnitude, float direction)
		{
			applyForce(Vector2(glm::cos(direction), glm::sin(direction)) * magnitude);
		}

		void onGameStep(float delta) override
		{

			if (friction > 0.f)
			{
				float scalarVelocity = glm::length(velocity);
				if (scalarVelocity > 0.f)
				{
					Vector2 normalizedVelocity = glm::normalize(velocity);
					float scalarProduct = glm::max(0.f, scalarVelocity - friction * delta);

					velocity = normalizedVelocity * scalarProduct;
				}
			};

			position += velocity * delta;
		}
	};

}
