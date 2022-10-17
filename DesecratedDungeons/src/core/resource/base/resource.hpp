#pragma once

#include <libraries.hpp>


namespace Desdun
{

	class Resource
	{
	public:
		Resource() = default;
		virtual ~Resource() = default;

		virtual void Load(const std::string& path) = 0;

		std::string GetPath() const { return Path; };

	protected:
		std::string Path = "";
		
	};

}