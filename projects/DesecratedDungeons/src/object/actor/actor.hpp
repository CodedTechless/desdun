#pragma once

#include <game_lib.hpp>

#include <scene/scene.h>

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