#include "colour.hpp"


namespace Desdun
{
	Color4f Color::fromRGB(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
	{
		return Color4f(r, g, b, a) / 255.f;
	}
}
