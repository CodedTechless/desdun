#pragma once

#include <core_lib.hpp>


namespace Desdun
{
	class Resource;
	using ResourceMap = Map<Type, Map<String, Resource*>>;

	class MissingResourceException : public virtual Exception
	{
	public:
		MissingResourceException(const String& name)
			: Exception(std::format("Resource {} does not exist.", name)) {};
	};

	class Resource
	{
	public:
		Resource() = default;
		~Resource();

		String getPath() const;

		static String transformPath(const String& path);

		static void reloadAll()
		{
			for (auto& resType : resources)
			{
				for (auto& res : resType.second)
				{
					res.second->reload();
				}

				Debug::Log("Reloaded " + std::string(resType.first.name()), "Resource Manager");
			}

			Debug::Log("Reloaded all assets", "Resource Manager");
		}
				
		template<typename T>
		static T* fetch(const String& rawPath, bool forceReload = false)
		{
			String path = transformPath(rawPath);

			fs::path location = fs::proximate(path);
			String pathString = location.generic_string();

			Type typeId = typeid(T);
			auto it = resources[typeId].find(pathString);

			if (it != resources[typeId].end())
			{
				T* res = (T*)it->second;

				if (forceReload)
				{
					res->reload();
					Debug::Log("Reloaded " + std::string(typeId.name()) + " " + pathString, "Resource Manager");
				}
				
				return res;
			}
			else
			{
				T* res = new T();

				if (fs::exists(location))
				{
					res->path = pathString;
				}
				else if (placeholders.find(typeId) != placeholders.end())
				{
					res->path = getPlaceholder<T>();
					Debug::Log("Missing " + typeName + " " + pathString, "Resource Manager");
				}
				else
				{
					throw MissingResourceException(path);
				}

				res->reload();

				resources[typeId][pathString] = res;

				String typeName = typeId.name();
				Debug::Log("Loaded " + typeName + " " + pathString, "Resource Manager");

				return res;
			}
		}

		template<typename T>
		static void getPlaceholder()
		{
			return placeholders[typeid(T)];
		}

	protected:

		bool loaded = false;

		void reload();
		virtual void load() = 0;
		virtual void unload() = 0;

	private:

		String path = "";
		static ResourceMap resources;
		static Map<Type, String> placeholders;

		template<typename T>
		static void setPlaceholder(const String& rawPath)
		{
			placeholders[typeid(T)] = rawPath;
		}

		friend class Application;

	};
}