#pragma once

#include <resource/serial/json_stream.h>

#include <core_lib.hpp>

namespace Desdun
{

	class InvalidClassFetchException : public virtual Exception
	{
	public:
		InvalidClassFetchException(const String& name)
			: Exception(std::format("Attempted to perform runtime class metadata fetch on {}, which does not exist.", name)) {};

	};

	class Serialisable
	{
	public:
		virtual std::type_index getClassIndex() const
		{
			return typeid(Serialisable);
		};

		virtual void serialise(JSONObject& object) const = 0;
		virtual void deserialise(const JSONObject& object) = 0;
	};

	class BaseRuntimeClass
	{
	public:

		BaseRuntimeClass() = delete;
		BaseRuntimeClass(const std::string& name, std::type_index linkedType, BaseRuntimeClass* inherits = nullptr)
			: m_TypeName(name), m_Index(linkedType), m_Inheritor(inherits) {};

		virtual Serialisable* New() const = 0;

		const std::string GetTypeName() const { return m_TypeName; };

		template<typename T>
		bool isA() const
		{
			if (m_Inheritor)
			{
				if (m_Index == std::type_index(typeid(T)))
				{
					return true;
				}
				else
				{
					return m_Inheritor->isA<T>();
				}
			}

			return false;
		}
	
	private:

		std::string m_TypeName;

		std::type_index m_Index;
		BaseRuntimeClass* m_Inheritor;

		friend class Runtime;

	};

	template<typename T>
	class RuntimeClass : public BaseRuntimeClass
	{
	public:
		RuntimeClass(const std::string& typeName, BaseRuntimeClass* inherits = nullptr)
			: BaseRuntimeClass(typeName, typeid(T), inherits) {};

		[[deprecated("Use RuntimeClass::create instead.")]]
		T* New() const
		{
			return new T();
		}

		T* create() const
		{
			return new T();
		}
	};

	class Runtime
	{
	public:

		static void start();

		template<typename T>
		static RuntimeClass<T>* registerClass(const std::string& typeName, BaseRuntimeClass* inherits = nullptr)
		{
			RuntimeClass<T>* newType = new RuntimeClass<T>(typeName, inherits);

			std::type_index Index = typeid(T);
			TypeCollection[Index] = newType;
			TypeNameIndexCollection[typeName] = newType;

#ifdef _DEBUG
			if (inherits)
				Debug::Log("Added new RuntimeClass " + typeName + " (inherited from " + inherits->m_TypeName + ")", "Runtime");
			else
				Debug::Log("Added new RuntimeClass " + typeName, "Runtime");
#endif

			return newType;
		}

		template<typename runtimeType>
		static RuntimeClass<runtimeType>* Get()
		{
			auto it = TypeCollection.find(typeid(runtimeType));
			if (it != TypeCollection.end())
			{
				return (RuntimeClass<runtimeType>*)it->second;
			}
			else
			{
				throw InvalidClassFetchException(typeid(runtimeType).name());
			}

			return nullptr;
		}

		static BaseRuntimeClass* Get(const std::string& typeName)
		{
			return TypeNameIndexCollection[typeName];
		}

		static BaseRuntimeClass* Get(std::type_index typeIndex)
		{
			return TypeCollection[typeIndex];
		}

	private:

		static std::unordered_map<std::type_index, BaseRuntimeClass*> TypeCollection;
		static std::unordered_map<std::string, BaseRuntimeClass*> TypeNameIndexCollection;

	};

}
