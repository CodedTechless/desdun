#pragma once

#include <libraries.hpp>

namespace Desdun
{

	class Runtime;
	class Instance;

	struct BaseRuntimeClass
	{
	public:

		BaseRuntimeClass() = delete;
		BaseRuntimeClass(const std::string& name, std::type_index linkedType, BaseRuntimeClass* inherits = nullptr)
			: m_TypeName(name), m_Index(linkedType), m_Inheritor(inherits) {};

		virtual Instance* New() const 
		{ 
			throw std::runtime_error("Cannot create a blank class; type specification required.");

			return nullptr;
		};

		const std::string GetTypeName() const { return m_TypeName; };

		template<typename T>
		bool IsA() const
		{
			if (m_Inheritor)
			{
				if (m_Index == std::type_index(typeid(T)))
				{
					return true;
				}
				else
				{
					return m_Inheritor->IsA<T>();
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
	struct RuntimeClass : public BaseRuntimeClass
	{
		RuntimeClass(const std::string& typeName, BaseRuntimeClass* inherits = nullptr)
			: BaseRuntimeClass(typeName, typeid(T), inherits) {};

		Instance* New() const
		{
			return new T();
		}
	};

	class Runtime
	{
	public:

		static void Start();

		template<typename T>
		static RuntimeClass<T>* Add(const std::string& typeName, BaseRuntimeClass* inherits = nullptr)
		{
			RuntimeClass<T>* newType = new RuntimeClass<T>(typeName, inherits);

			std::type_index Index = typeid(T);
			TypeCollection[Index] = newType;
			TypeNameIndexCollection[typeName] = newType;

#ifdef _DEBUG
			if (inherits)
				Debug::Log("Added new RuntimeClass " + typeName + " (inherited from " + inherits->m_TypeName + ")", "Runtime");
			else
				Debug::Log("Added new RuntimeClass " + typeName, "Instance");
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
				throw Exception("Class fetch failed; doesn't exist.");
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
