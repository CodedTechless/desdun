#pragma once


#include "serial_object.hpp"

namespace DesdunCore
{
	class BaseRuntimeClass
	{
	public:

		BaseRuntimeClass() = delete;

		BaseRuntimeClass(const String& type_name, Type type_index);
		BaseRuntimeClass(const String& type_name, Type type_index, InitList<BaseRuntimeClass*> inherits_from);

		virtual Serialisable* create() const = 0;

		const List<BaseRuntimeClass*>& getParents();
		const String getName() const;
		Type getIndex() const;

		template<typename T>
		bool isA() const
		{
			if (inheritsFrom.empty() == false)
			{
				if (typeIndex == Type(typeid(T)))
				{
					return true;
				}
				else
				{
					for (auto* parentClass : inheritsFrom)
					{
						if (parentClass->isA<T>() == true)
						{
							return true;
						}
					}
				}
			}

			return false;
		}

	private:

		std::string typeName;

		std::type_index typeIndex;
		List<BaseRuntimeClass*> inheritsFrom;

		friend class Runtime;

	};

	template<typename T>
	class RuntimeClass : public BaseRuntimeClass
	{
	public:

		RuntimeClass(const String& type_name)
			: BaseRuntimeClass(type_name, typeid(T)) {};

		RuntimeClass(const String& type_name, BaseRuntimeClass* inherits_from)
			: BaseRuntimeClass(type_name, typeid(T), { inherits_from }) {};

		RuntimeClass(const String& type_name, InitList<BaseRuntimeClass*> inherits_from)
			: BaseRuntimeClass(type_name, typeid(T), inherits_from) {};

		T* create() const
		{
			return new T();
		}
	};
}