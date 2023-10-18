#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <cstddef>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <bitset>
#include <stack>
#include <algorithm>
#include <functional>
#include <regex>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>
#include <iostream>

#include <sstream>

#include <app/debug/debug.hpp>

#include <corelib/alias/base.hpp>
#include <corelib/alias/colour.hpp>
#include <corelib/math/math.hpp>
#include <corelib/math/spatial_hash_map.hpp>
#include <corelib/math/uuid.hpp>

#include <lua/lua.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <json/json.hpp>

#define MAX_INSTANCES 8192
#define COLLISION_MAP_SIZE 2048
#define COLLISION_MAP_CELL_SIZE 64

#define bytelen(ptrArray, ptrHead) (uint32_t)((uint8_t*)ptrHead - (uint8_t*)ptrArray)

#define dd_class(T) Runtime::add<T>({ #T })
#define dd_class_child(bT, iT) Runtime::add<bT>({ #bT, Runtime::get<iT>() })

#define dd_serialisable(T) public: \
const std::string getClassName() const override { return #T; }; \
std::type_index getClassIndex() const override { return typeid(T); };

#if DEBUG
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

namespace DesdunCore
{
	namespace fs = std::filesystem;
	using json = nlohmann::json;
}

namespace glm
{

	void to_json(DesdunCore::json& jsonObject, const glm::vec2& vec);
	void to_json(DesdunCore::json& jsonObject, const glm::vec3& vec);
	void to_json(DesdunCore::json& jsonObject, const glm::vec4& vec);

	void from_json(const DesdunCore::json& j, glm::vec2& vec);
	void from_json(const DesdunCore::json& j, glm::vec3& vec);
	void from_json(const DesdunCore::json& j, glm::vec4& vec);

}

