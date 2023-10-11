#pragma once

#include <typeindex>
#include <array>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>

namespace Desdun
{

	using FLAG = bool;
	using uint = uint32_t;
	using uchar = uint8_t;
	using byte = unsigned char;

	using String = std::basic_string<char, std::char_traits<char>, std::allocator<char>>;
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

}