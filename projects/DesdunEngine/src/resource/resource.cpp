

#include "resource.hpp"


namespace Desdun
{

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