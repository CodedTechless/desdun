#pragma once

#include <libraries.hpp>

namespace Desdun
{

	class ResourceLoader
	{
	public:

		static void Read(const std::string& path, const std::string& extension, std::vector<fs::directory_entry>& files)
		{
			for (const fs::directory_entry& File : fs::directory_iterator(path))
			{
				fs::path d_Path = File.path();

				if (File.is_directory())
				{
					Read(d_Path.generic_string(), extension, files);
				}
				else if (File.is_regular_file() && d_Path.extension().generic_string() == extension)
				{
					files.push_back(File);
				}
			}
		}

	};

}