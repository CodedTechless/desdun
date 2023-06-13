#include "util.hpp"

namespace Desdun
{
    bool util::checkRect(const Vector2 pos1, const Vector2 size1, const Vector2 pos2, const Vector2 size2)
    {
        return pos1.x + size1.x >= pos2.x &&
            pos1.x <= pos2.x + size2.x &&
            pos1.y + size1.y >= pos2.y &&
            pos1.y <= pos2.y + size2.y;
    }
}
