

#include "resource.hpp"


namespace DesdunCore
{

	ResourceMap Resource::resources = {};
	Map<Type, String> Resource::placeholders = {};

	Resource::~Resource()
	{
		unload();
	}

	void Resource::reload()
	{
		if (loaded) unload();
		load();
	}

	String Resource::getPath() const
	{
		return path;
	};

	String Resource::transformPath(const String& basePath)
	{
		std::smatch res = {};
		bool canTransform = std::regex_search(basePath, res, std::regex("^[a-z]+(?=:)"));
		String path = basePath;

		if (canTransform)
		{
			path = std::regex_replace(basePath, std::regex("^[a-z]+:"), "assets/" + res.str() + "/");
		}

		return path;
	}

}