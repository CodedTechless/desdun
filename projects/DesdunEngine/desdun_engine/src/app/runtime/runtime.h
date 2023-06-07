#pragma once

#include "base/runtime_obj.h"

namespace Desdun
{

	class InvalidClassFetchException : public virtual Exception
	{
	public:
		InvalidClassFetchException(const String& name)
			: Exception(std::format("Attempted to perform runtime class metadata fetch on {}, which does not exist.", name)) {};

	};

	class Runtime
	{
	public:

		template<typename T>
		static RuntimeClass<T>* add(RuntimeClass<T> runtimeClass)
		{
			RuntimeClass<T>* newType = new RuntimeClass<T>(runtimeClass);

			Type idx = typeid(T);
			types[newType->getIndex()] = newType;
			typeNames[newType->getName()] = newType;

#if _DEBUG
			String inheritsList = "";
			for (auto* parentClass : newType->getParents())
			{
				inheritsList.append(parentClass->getName() + " ");
			}

			if (inheritsList.empty())
				Debug::Log("Registered class " + newType->getName(), "Runtime");
			else
				Debug::Log("Registered class " + newType->getName() + " which inherits " + inheritsList, "Runtime");
#endif

			return newType;
		}

		template<typename T>
		static RuntimeClass<T>* get()
		{
			auto it = types.find(typeid(T));
			if (it != types.end())
			{
				return (RuntimeClass<T>*)it->second;
			}
			else
			{
				throw InvalidClassFetchException(typeid(T).name());
			}

			return nullptr;
		}

		static BaseRuntimeClass* get(const String& typeName)
		{
			return typeNames[typeName];
		}

		static BaseRuntimeClass* get(Type typeIndex)
		{
			return types[typeIndex];
		}

	private:

		static Map<Type, BaseRuntimeClass*> types;
		static Map<String, BaseRuntimeClass*> typeNames;

	};

}
