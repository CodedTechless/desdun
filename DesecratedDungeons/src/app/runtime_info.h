#pragma once

#include <object/instance.h>

#include <libraries.hpp>

namespace Desdun
{

	struct RuntimeType
	{
		RuntimeType() = default;

		const std::string GetTypeName() const { return m_TypeName; };

	private:

		std::string m_TypeName = {};
		std::vector<std::type_index> m_Descendants = {};

		std::type_index m_Index;

		friend class Runtime;

	};



	class Runtime
	{
	public:

		template<typename T>
		static void Add(const std::string& name, std::initializer_list<ClassModifier> modifiers = {})
		{
			std::type_index Index = typeid(T);

			RuntimeType newType;

			newType.m_TypeName = name;
			newType.m_Index = Index;


			Types[Index] = newType;
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
