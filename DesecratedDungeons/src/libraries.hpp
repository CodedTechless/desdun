#pragma once

#define PI 3.14159265358979323846   // pi

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstddef>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <filesystem>
#include <string>

#include <unordered_map>
#include <vector>
#include <array>
#include <algorithm>

#include <typeindex>

#include <fstream>

#include <functional>

#include <app/debug/debug.h>
#include <glm/glm.hpp>

#define MAX_INSTANCES 4196

namespace fs = std::filesystem;

namespace Desdun
{
	using FLAG = bool;

	using uint = unsigned int;
	using uchar = unsigned char;

	using Vector2 = glm::vec<2, float>;
	using Vector3 = glm::vec<3, float>;
	using Vector4 = glm::vec<4, float>;

	using Vector2i = glm::vec<2, int>;
	using Vector3i = glm::vec<3, int>;
	using Vector4i = glm::vec<4, int>;

	using Vector2u = glm::vec<2, uint>;
	using Vector3u = glm::vec<3, uint>;
	using Vector4u = glm::vec<4, uint>;

	using Color4 = glm::vec<4, float>;
	using Mat4 = glm::mat<4, 4, glm::f32, glm::defaultp>;

	template <typename T>
	using ptr = std::shared_ptr<T>;

	template <typename T>
	using uptr = std::unique_ptr<T>;

	template <typename T, typename ...Args>
	constexpr ptr<T> CreatePointer(Args&& ...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	constexpr int sign(T val) {
		return (T(0) < val) - (val < T(0));
	}
}