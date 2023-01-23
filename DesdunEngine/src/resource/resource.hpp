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

		virtual void Load(const std::string& path) = 0;

		std::string GetPath() const { return Path; };

		// Static fetch function for resources
		
		template<typename T>
		static T* Fetch(const std::string& path)
		{
			fs::path Location = fs::proximate(path);

			if (!fs::exists(Location))
			{
				throw Exception("Resource " + Location.generic_string() + " does not exist!");
			}

			std::type_index Type = typeid(T);
			std::string PathString = Location.generic_string();
			std::string Name = Type.name();

			auto it = Resources[Type].find(PathString);
			if (it != Resources[Type].end())
			{
				Debug::Log("Found cached resource for " + std::string(Name) + " " + PathString);
				return (T*)it->second;
			}
			else
			{
				T* NewResource = new T();
				NewResource->Load(path);

				Debug::Log("Loaded " + Name + " " + PathString);

				Resources[Type][PathString] = NewResource;

				return NewResource;
			}
		}

	protected:

		std::string Path = "";
		
	private:

		static ResourceMap Resources;
	};

}