#pragma once

#include <object/types/object.h>

namespace Desdun
{
	
	class PhysicsBody : public Object
	{
	public:
		RUNTIME_CLASS_DEF(PhysicsBody);
		
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


			// assign those cells
		};

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
		void assign()
		{
			// remove the old assigned cells (if there are any)
			for (Vector2 cellPos : ownedCells)
			{
				auto& linkedObjects = getScene()->collisionMap[cellPos.x][cellPos.y];
				
				auto it = std::find(linkedObjects.begin(), linkedObjects.end(), this);
				if (it != linkedObjects.end())
				{
					linkedObjects.erase(it);
				}
			}

			ownedCells.clear();

			// figure out what new cells we have to take up


			// assign those cells in the grid
			for (Vector2 cellPos : ownedCells)
			{
				auto& linkedObjects = getScene()->collisionMap[cellPos.x][cellPos.y];
				linkedObjects.push_back(this);
			}
		}

		std::vector<Vector2> ownedCells = {};

		Shape collisionShape = {};
		
	};
}

