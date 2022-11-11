#pragma once

/*
	helper class for reading binary files. manages opening/closing for you.
*/

#include <libraries.hpp>

namespace Desdun
{

	

	class ByteFile
	{
	public:
		ByteFile(const std::string& name)
			: Name(name) {};

		~ByteFile();

		enum class Mode
		{
			Read,
			Write
		};

		template<typename T>
		void operator<<(T* source) 
		{ 
			write(source); 
		};

		template<typename T>
		void operator<<(T val)
		{
			write(&val);
		};

		template<typename T>
		void operator>>(T* destination) 
		{ 
			read_to(destination); 
		};

		void operator<<(const std::string& val)
		{
			size_t len = val.size();
			const char* arr = val.c_str();

			write(&len);

			if (len > 0)
				write(arr, len);
		}

		void operator>>(std::string& destination)
		{
			size_t len;
			read_to(&len);

			if (len > 0)
			{
				char* arr = new char[len]();
				read_to(arr, len);

				destination.assign(arr, len);
			}
		}

		template<typename T>
		void write(T* buffer, size_t count = 1)
		{
			SetMode(ByteFile::Mode::Write);

			OutputStream.write((char*)buffer, sizeof(T) * count);
		}

		template<typename T>
		void read_to(T* destination, size_t count = 1)
		{
			SetMode(ByteFile::Mode::Read);

			InputStream.read((char*)destination, sizeof(T) * count);
		}

	private:

		std::string Name;

		std::ofstream OutputStream;
		std::ifstream InputStream;

		void SetMode(Mode streamMode);

	};

}