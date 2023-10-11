#pragma once

#include <corelib/core.hpp>

namespace Desdun
{

	class Primitive
	{
	public:

		static void drawRect(Vector2 position, Vector2 size, float zIndex = 0.f, float rotation = 0.f, Color4 tint = { 1.f, 1.f, 1.f, 1.f });
		static void drawLine(const Vector2& p0, const Vector2& p1, const Color4f tint = { 1.f, 1.f, 1.f, 1.f });

	};

}