#pragma once

#include <core/resource/base/resource.hpp>
#include <core/resource/external/image.h>
#include <libraries.hpp>

namespace Desdun
{
	using ResourceCache = std::unordered_map<const char*, std::unordered_map<std::string, Resource*>>;

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

			auto Name = Location.generic_string();
			auto* Type = typeid(T).name();

			auto it = Resources[Type].find(Name);
			if (it != Resources[Type].end())
			{
				return (T*)it->second;
			}

			T* NewResource = new T();
			NewResource->Load(path);

			Resources[Type][Name] = NewResource;

			return NewResource;
		}

	private:

		static ResourceCache Resources;

	};

	ResourceCache ResourceService::Resources = {};

}