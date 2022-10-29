#pragma once

#include <libraries.hpp>


namespace Desdun
{

	namespace Enum
	{
		enum class ResourceType
		{
			None = 0,
			Image = 1,
			Audio = 2,
			Shader = 3
		};
	}

	class Resource
	{
	public:
		Resource() = default;
		virtual ~Resource() = default;

		virtual void Load(const std::string& path) = 0;

		std::string GetPath() const { return Path; };
		Enum::ResourceType GetType() const { return Type; };

	protected:
		std::string Path = "";

		Enum::ResourceType Type = Enum::ResourceType::None;
		
	};

}