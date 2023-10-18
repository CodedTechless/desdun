#pragma once

#include <objects/types/2d/entity.hpp>

namespace DesdunCore
{

	class Actor : public Entity2D
	{
	public:
		dd_serialisable(Actor);

		float health = 100.f;
		float maxHealth = 100.f;

		void takeDamage(float amount);

	protected:

		void serialise(JSONObject& object) const override;
		void deserialise(const JSONObject& object) override;

	};
}