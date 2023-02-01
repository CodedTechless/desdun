

#include "actor.hpp"


namespace Desdun
{

	void Actor::takeDamage(float amount)
	{

	};

	void Actor::serialise(JSONObject& object) const
	{
		object["health"] = health;
		object["maxHealth"] = maxHealth;

		Object::serialise(object);
	}

	void Actor::deserialise(const JSONObject& object)
	{
		object.at("health").get_to(health);
		object.at("maxHealth").get_to(maxHealth);

		Object::deserialise(object);
	}
}