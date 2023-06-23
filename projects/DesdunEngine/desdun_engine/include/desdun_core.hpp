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
#include <regex>

#include <desdun_engine/src/app/debug/debug.h>

#include <desdun_engine/include/json/json.hpp>
#include <desdun_engine/include/glm/glm.hpp>
#include <desdun_engine/include/glm/gtx/compatibility.hpp>

#define MAX_INSTANCES 8192
#define COLLISION_MAP_SIZE 2048
#define COLLISION_MAP_CELL_SIZE 64

#define bytelen(ptrArray, ptrHead) (uint32_t)((uint8_t*)ptrHead - (uint8_t*)ptrArray)

#define dd_class(T) Runtime::add<T>({ #T })
#define dd_class_child(bT, iT) Runtime::add<bT>({ #bT, Runtime::get<iT>() })

#define serialisable(T) public: \
const std::string getClassName() const override { return #T; }; \
std::type_index getClassIndex() const override { return typeid(T); };

#if _DEBUG
#define dd_log(str) Debug::Log(str)
#define dd_warn(str) Debug::Warn(str)
#define dd_error(str) Debug::Error(str)

#define dd_log_h(str, header) Debug::Log(str, header)
#define dd_warn_h(str, header) Debug::Warn(str, header)
#define dd_error_h(str, header) Debug::Error(str, header)

#define dd_log_f(fmt, ...) Debug::Log(std::format(fmt, __VA_ARGS__))
#define dd_warn_f(fmt, ...) Debug::Warn(std::format(fmt, __VA_ARGS__))
#define dd_error_f(fmt, ...) Debug::Error(std::format(fmt, __VA_ARGS__))

#define dd_log_fh(fmt, header, ...) Debug::Log(std::format(fmt, __VA_ARGS__), header)
#define dd_warn_fh(fmt, header, ...) Debug::Warn(std::format(fmt, __VA_ARGS__), header)
#define dd_error_fh(fmt, header, ...) Debug::Error(std::format(fmt, __VA_ARGS__), header)
#else
#define dd_log()
#define dd_warn()
#define dd_error()

#define dd_log_f()
#define dd_warn_f()
#define dd_error_f()

#define dd_log_fh()
#define dd_warn_fh()
#define dd_error_fh()
#endif

#define s_errout(name, res) Debug::Error(std::format("Failed to load symbol {}: {}", #name, res), "JSONStream")
#define s_wrap(name, op) try { op; } catch(std::exception err) { s_errout(name, err.what()); }

#define s_export(name) object[#name] = name
#define s_import(name) s_wrap(name, { object.at(#name).get_to(name); })

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
	template<size_t size>
	using FLAG_SET = std::bitset<size>;

	using FLAG = bool;
	using uint = uint32_t;
	using uchar = uint8_t;
	using byte = unsigned char;
	using String = std::string;
	using Type = std::type_index;

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

	template<typename k, typename v>
	using Map = std::unordered_map<k, v>;

	template<typename T>
	using List = std::vector<T>;

	template<typename T>
	using InitList = std::initializer_list<T>;

	template<typename T, size_t size>
	using Array = std::array<T, size>;

	using Mat4 = glm::mat<4, 4, glm::f32, glm::defaultp>;
	using Mat4f = glm::mat<4, 4, glm::f32, glm::defaultp>;

	class Exception : public std::runtime_error
	{
	public:
		explicit Exception(const String& message)
			: std::runtime_error(message) {};
	};

	template<typename T>
	using Provider = std::function<T* ()>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using StrictRef = std::unique_ptr<T>;

	template<typename T, typename ...Args>
	constexpr Ref<T> CreateRef(Args&& ...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	constexpr int sign(T val)
	{
		return (T(0) < val) - (val < T(0));
	}

	// using Ref is preferred, this is only here for backwards compat
	template <typename T>
	using ptr = std::shared_ptr<T>;

	template <typename T>
	using uptr = std::unique_ptr<T>;

	template <typename T, typename ...Args>
	[[deprecated("Use 'CreateRef' instead.")]]
	constexpr ptr<T> CreatePointer(Args&& ...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	namespace math
	{
		constexpr float_t PI2 = PI * 2.f;

		template <typename T = float>
		T rlerp(T b, T a, T alpha)
		{
			T da = std::fmod(a - b, PI2);
			return b + (std::fmod(2.f * da, PI2) - da) * alpha;
		}
	}

	
}