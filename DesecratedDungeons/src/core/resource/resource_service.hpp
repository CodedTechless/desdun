#pragma once

#include <core/resource/base/resource.hpp>
#include <libraries.hpp>

namespace Desdun
{
	using ResourceCache = std::unordered_map<fs::path, ptr<Resource>>;

	class ResourceService
	{
	public:

		template<typename T>
		static ptr<T> Fetch(const std::string& path)
		{
			fs::path Location = fs::proximate(path);

			auto it = Resources.find(Location);
			if (it != Resources.end())
			{
				return std::static_pointer_cast<T>(it->second);
			}

			ptr<T> NewResource = CreatePointer<T>();
			NewResource->Load(path);

			Resources[Location] = std::static_pointer_cast<Resource>(NewResource);

			return NewResource;
		}

	private:
		static ResourceCache Resources;

	};

	ResourceCache ResourceService::Resources = {};

}