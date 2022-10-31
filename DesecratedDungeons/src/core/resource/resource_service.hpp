#pragma once

#include <core/resource/resource.hpp>
#include <core/resource/types/image.h>
#include <libraries.hpp>

namespace Desdun
{
	using ResourceMap = std::unordered_map<std::string, std::unordered_map<std::string, Resource*>>;

	class ResourceService
	{
	public:

		template<typename T>
		static T* Fetch(const std::string& path)
		{
			fs::path Location = fs::proximate(path);

			if (!fs::exists(Location))
			{
				Debug::Error("No such resource as '" + path + "'!");
				return nullptr;
			}

			std::string Name = Location.generic_string();
			std::string Type = (std::string)typeid(T).name();

			auto it = Resources[Type].find(Name);
			if (it != Resources[Type].end())
			{
				Debug::Log("Found cached resource for " + Type + " " + Name);
				return (T*)it->second;
			}

			T* NewResource = new T();
			NewResource->Load(path);

			Debug::Log("Loaded " + std::string(Type) + " " + Name);

			Resources[Type][Name] = NewResource;

			return NewResource;
		}

	private:

		static ResourceMap Resources;

	};

}