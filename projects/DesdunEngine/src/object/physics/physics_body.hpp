#pragma once

#include <object/object.h>

namespace Desdun
{
	
	class PhysicsBody : public WorldObject
	{
	public:
		serialisable(PhysicsBody)

		enum class ShapeType
		{
			None,
			Rectangle
		};

		struct Shape
		{
			ShapeType type = ShapeType::Rectangle;
			Vector2 size = { 32.f, 32.f };
		};

		std::bitset<32> layer = {};
		std::bitset<32> mask = {};

		/*
			sets a new collision shape and then runs assign() to update the collision grid of its
			new information
		*/
		void setCollisionShape(Shape shape)
		{
			collisionShape = shape;
			assign();
		};

		Shape getCollisionShape() const
		{
			return collisionShape;
		}

		const std::vector<Vector2>& getOwnedCells() const
		{
			return ownedCells;
		}

	private:

		/*
			this function should manage assigning the current shape to the grid
			this will also manage unallocating previous spaces that were taken up
			in the collision grid, in the case of some sort of change in the objects
			position.
			
			usually, the object shouldn't have changed position (in the case of a
			static physics object), but if it has, then this will manage the unassignment
			process too.
		*/
		void assign();

		std::vector<Vector2> ownedCells = {};

		Shape collisionShape = {};
		
	};
}

