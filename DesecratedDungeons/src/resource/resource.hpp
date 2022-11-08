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

	class Resource;

	using ResourceMap = std::unordered_map<std::string, std::unordered_map<std::string, Resource*>>;

	class Resource
	{
	public:
		Resource() = default;
		virtual ~Resource() = default;

		virtual void Load(const std::string& path) = 0;

		std::string GetPath() const { return Path; };

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

	protected:

		std::string Path = "";
		
	private:

		static ResourceMap Resources;
	};

}