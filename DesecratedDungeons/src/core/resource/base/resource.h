#pragma once

#include <libraries.hpp>


namespace Desdun
{

	class Resource
	{
	public:
		Resource() = default;
		virtual ~Resource() = 0;

		virtual void Load(const std::string& path) = 0;

	protected:
		std::string Path = "";
		bool Loaded = false;

	};

}