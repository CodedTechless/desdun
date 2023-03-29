#pragma once

#include <core_lib.hpp>


namespace Desdun
{
	class Resource;
	using ResourceMap = Map<Type, Map<String, Resource*>>;

	class MissingResourceException : public virtual Exception
	{
	public:
		MissingResourceException(const String& name)
			: Exception(std::format("Resource {} does not exist.", name)) {};
	};

	class Resource
	{
	public:
		Resource() = default;
		virtual ~Resource() = default;

		virtual void load(const std::string& path) = 0;
		String getPath() const { return Path; };

		static String transformPath(const String& path);
		static const ResourceMap& getResources() { return resources; };

		// Static fetch function for resources
		
		template<typename T>
		static T* fetch(const String& rawPath)
		{
			String path = transformPath(rawPath);
			fs::path location = fs::proximate(path);

			if (!fs::exists(location))
				throw MissingResourceException(rawPath);

			Type typeId = typeid(T);
			String pathString = location.generic_string();

			auto it = resources[typeId].find(pathString);
			if (it != resources[typeId].end())
			{
				//Debug::Log("Found cached resource for " + std::string(Name) + " " + PathString);
				return (T*)it->second;
			}
			else
			{
				T* NewResource = new T();
				NewResource->load(pathString);
				resources[typeId][pathString] = NewResource;

				String typeName = typeId.name();
				Debug::Log("Loaded " + typeName + " " + pathString, "Resource Manager");

				return NewResource;
			}
		}

	protected:
		String Path = "";
	private:
		static ResourceMap resources;
	};

}