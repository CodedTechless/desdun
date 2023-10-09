#pragma once


#include <include/glm/glm.hpp>

namespace Desdun
{

	namespace math
	{
		constexpr float_t PI = 3.1415926536f;
		constexpr float_t PI2 = PI * 2.f;

		template <typename T>
		int sign(T val)
		{
			return (T(0) < val) - (val < T(0));
		}

		template <typename T = float>
		T rlerp(T b, T a, T alpha)
		{
			T da = std::fmod(a - b, PI2);
			return b + (std::fmod(2.f * da, PI2) - da) * alpha;
		}

		bool checkRect(glm::vec2 p1, glm::vec2 s1, glm::vec2 p2, glm::vec2 s2);
	}

}