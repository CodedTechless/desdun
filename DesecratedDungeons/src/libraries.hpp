#pragma once

#define PI 3.14159265358979323846   // pi

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
#include <stack>
#include <array>
#include <algorithm>
#include <typeindex>
#include <functional>

#include <app/debug/debug.h>

#include <json/json.hpp>
#include <glm/glm.hpp>

#define MAX_INSTANCES 4196

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace glm
{

	void to_json(json& jsonObject, const glm::vec2& vec)
	{
		jsonObject = {
			{ "x", vec.x },
			{ "y", vec.y }
		};
	};

	void to_json(json& jsonObject, const glm::vec3& vec)
	{
		jsonObject = {
			{ "x", vec.x },
			{ "y", vec.y },
			{ "z", vec.z }
		};
	};

	void to_json(json& jsonObject, const glm::vec4& vec)
	{
		jsonObject = {
			{ "x", vec.x },
			{ "y", vec.y },
			{ "z", vec.z },
			{ "w", vec.w }
		};
	};

	void from_json(const json& j, glm::vec2& vec)
	{
		vec = glm::vec2(
			j.at("x"), 
			j.at("y")
		);
	};

	void from_json(const json& j, glm::vec3& vec)
	{
		vec = glm::vec3(
			j.at("x"), 
			j.at("y"),
			j.at("z")
		);
	};

	void from_json(const json& j, glm::vec4& vec)
	{
		vec = glm::vec4(
			j.at("x"), 
			j.at("y"),
			j.at("z"),
			j.at("w")
		);
	};

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

	using uint = uint64_t;
	using uchar = uint8_t;
	using byte = unsigned char;

	using string = std::wstring;

	using Vector2 = glm::vec<2, double_t>;
	using Vector3 = glm::vec<3, double_t>;
	using Vector4 = glm::vec<4, double_t>;

	using Vector2i = glm::vec<2, int64_t>;
	using Vector3i = glm::vec<3, int64_t>;
	using Vector4i = glm::vec<4, int64_t>;

	using Vector2u = glm::vec<2, uint64_t>;
	using Vector3u = glm::vec<3, uint64_t>;
	using Vector4u = glm::vec<4, uint64_t>;

	using Color4 = Vector4;
	using Mat4 = glm::mat<4, 4, glm::f64, glm::defaultp>;

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