#pragma once

#include <core_lib.hpp>


namespace Desdun
{
	class Resource;
	using ResourceMap = std::unordered_map<std::type_index, std::unordered_map<std::string, Resource*>>;

	class Resource
	{
	public:
		Resource() = default;
		virtual ~Resource() = default;

		virtual void load(const std::string& path) = 0;

		std::string getPath() const { return Path; };
		static const ResourceMap& getResources() { return resources; };

		// Static fetch function for resources
		
		template<typename T>
		static T* fetch(const std::string& path)
		{
			fs::path Location = fs::proximate(path);

			if (!fs::exists(Location))
			{
				throw Exception("Resource " + Location.generic_string() + " does not exist!");
			}

			std::type_index Type = typeid(T);
			std::string PathString = Location.generic_string();
			std::string Name = Type.name();

			auto it = resources[Type].find(PathString);
			if (it != resources[Type].end())
			{
				//Debug::Log("Found cached resource for " + std::string(Name) + " " + PathString);
				return (T*)it->second;
			}
			else
			{
				T* NewResource = new T();
				NewResource->load(path);

				//Debug::Log("Loaded " + Name + " " + PathString);

				resources[Type][PathString] = NewResource;

				return NewResource;
			}
		}

	protected:

		std::string Path = "";
		
	private:

		static ResourceMap resources;
	};

}