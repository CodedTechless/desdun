#pragma once

#include <desdun_engine/desdun_engine.hpp>

namespace Desdun
{

	class Actor : public WorldObject
	{
	public:
		serialisable(Actor);

		float health = 100.f;
		float maxHealth = 100.f;

		void takeDamage(float amount);

	protected:

		void serialise(JSONObject& object) const override;
		void deserialise(const JSONObject& object) override;

	};
}