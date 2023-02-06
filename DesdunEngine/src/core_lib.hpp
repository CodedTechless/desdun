#pragma once

#define PI 3.1415926536f   // pi

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstddef>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#include <unordered_map>
#include <vector>
#include <bitset>
#include <stack>
#include <array>
#include <algorithm>
#include <typeindex>
#include <functional>

#include <app/debug/debug.h>

#include <json/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>

#define MAX_INSTANCES 8192
#define RUNTIME_CLASS_DEF(x) \
	std::type_index getClassIndex() const override { return typeid(x); } \

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace glm
{

	void to_json(json& jsonObject, const glm::vec2& vec);
	void to_json(json& jsonObject, const glm::vec3& vec);
	void to_json(json& jsonObject, const glm::vec4& vec);

	void from_json(const json& j, glm::vec2& vec);
	void from_json(const json& j, glm::vec3& vec);
	void from_json(const json& j, glm::vec4& vec);

}

namespace Desdun
{

	class Exception : public std::exception
	{
	public:
		Exception(const std::string& what)
			: std::exception(what.c_str()) {};
	};

	using FLAG = bool;

	using uint = uint32_t;
	using uchar = uint8_t;
	using byte = unsigned char;

	using Vector2 = glm::vec<2, float_t>;
	using Vector3 = glm::vec<3, float_t>;
	using Vector4 = glm::vec<4, float_t>;

	using Vector2f = glm::vec<2, float_t>;
	using Vector3f = glm::vec<3, float_t>;
	using Vector4f = glm::vec<4, float_t>;

	using Vector2i = glm::vec<2, int32_t>;
	using Vector3i = glm::vec<3, int32_t>;
	using Vector4i = glm::vec<4, int32_t>;

	using Vector2u = glm::vec<2, uint>;
	using Vector3u = glm::vec<3, uint>;
	using Vector4u = glm::vec<4, uint>;

	using Color4 = Vector4;
	using Color4f = Vector4f;

	using Mat4 = glm::mat<4, 4, glm::f32, glm::defaultp>;
	using Mat4f = glm::mat<4, 4, glm::f32, glm::defaultp>;

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