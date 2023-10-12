#pragma once

#include <objects/types/2d/entity.hpp>

namespace Desdun
{
	class TileMap : public Entity2D
	{
	public:
		serialisable(TileMap)
	};
}