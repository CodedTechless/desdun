#pragma once

#include <core/resource/base/resource.hpp>
#include <libraries.hpp>

namespace Desdun
{
	using ResourceCache = std::unordered_map<fs::path, Resource*>;

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

			auto it = Resources.find(Location);
			if (it != Resources.end())
			{
				return it->second;
			}

			T* NewResource = new T();
			NewResource->Load(path);

			Resources[Location.stem().generic_string()] = NewResource;

			return NewResource;
		}

	private:

		static ResourceCache Resources;

	};

	ResourceCache ResourceService::Resources = {};

}