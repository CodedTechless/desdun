#pragma once

#include <object/instance.h>

#include <libraries.hpp>

namespace Desdun
{

	struct RuntimeType
	{
		RuntimeType() = default;

		const std::string GetTypeName() const { return TypeName; };

	private:

		std::string TypeName = {};
		std::vector<std::type_index> Descendants = {};

		friend class RuntimeInfo;

	};

	struct BaseClassGeneric
	{

	};

	class Runtime
	{
	public:

		static void Add(const std::string& name, const RuntimeType& inherits)
		{

		}

		template<typename T>
		static const RuntimeType& Get()
		{
			return Types[typeid(T)];
		}

	private:

		static std::unordered_map<std::type_index, RuntimeType> Types;
		static std::unordered_map<std::string, std::function<Instance*()>> Constructors;
	};

}
