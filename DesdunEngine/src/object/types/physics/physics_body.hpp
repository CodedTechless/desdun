#pragma once

#include <object/types/object.h>

namespace Desdun
{
	class PhysicsBody : public Object
	{
	public:
		RUNTIME_CLASS_DEF(PhysicsBody);
		
		enum class Shape
		{
			None,
			Rectangle
		};

		std::bitset<32> layer = {};
		std::bitset<32> mask = {};

		Shape collisionShape = Shape::Rectangle;

	};
}

