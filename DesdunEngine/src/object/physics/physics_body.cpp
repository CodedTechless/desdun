
#include <scene/scene.h>

#include "physics_body.hpp"

namespace Desdun
{

	void PhysicsBody::assign()
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

		Vector2 fullSize = collisionShape.size * scale;

		Vector2 start = glm::floor((position - fullSize / 2.f) / (float)COLLISION_MAP_CELL_SIZE);
		Vector2 end = glm::ceil((position + fullSize / 2.f) / (float)COLLISION_MAP_CELL_SIZE);

		for (float ix = 0; ix < end.x - start.x; ix++)
		{
			for (float iy = 0; iy < end.y - start.y; iy++)
			{
				ownedCells.push_back({ ix, iy });
			}
		}

		// assign those cells in the grid
		for (Vector2 cellPos : ownedCells)
		{
			auto& linkedObjects = getScene()->collisionMap[cellPos.x][cellPos.y];
			linkedObjects.push_back(this);
		}
	}

}
