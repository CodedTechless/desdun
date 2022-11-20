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

		enum class Type
		{
			Null,
			Int,
			Double,
			Bool,
			String
		};

		enum class Mode
		{
			Read,
			Write
		};

		// Write

		void operator|(Type special)
		{
			char identity = (char)special;
			write_from(&identity);
		};

		void operator<<(int64_t source) 
		{
			char identity = (char)Type::Int;
			write_from(&identity);
			write_from(&source);
		}

		void operator<<(double_t source)
		{
			char identity = (char)Type::Double;
			write_from(&identity);
			write_from(&source);
		};

		void operator<<(bool source)
		{
			char identity = (char)Type::Bool;
			write_from(&identity);
			write_from(&source);
		};

		void operator<<(const std::string& source)
		{
			char identity = (char)Type::String;
			write_from(&identity);

			size_t len = source.size();
			const char* arr = source.c_str();

			write_from(&len);

			if (len > 0)
			{
				write_from(arr, len);
			}
		};

		void operator<<(int32_t source) { operator<<(static_cast<int64_t>(source)); };
		void operator<<(int16_t source) { operator<<(static_cast<int64_t>(source)); };
		void operator<<(int8_t source) { operator<<(static_cast<int64_t>(source)); };

		void operator<<(uint64_t source) { operator<<(static_cast<int64_t>(source)); };
		void operator<<(uint32_t source) { operator<<(static_cast<int64_t>(source)); };
		void operator<<(uint16_t source) { operator<<(static_cast<int64_t>(source)); };
		void operator<<(uint8_t source) { operator<<(static_cast<int64_t>(source)); };

		void operator<<(float_t source) { operator<<(static_cast<double_t>(source)); };

		// Read

		template<typename T>
		void operator>>(T* destination) 
		{ 
			// if we're doing an explicit read, we skip the type id. this is dangerous!!
			SetMode(ByteFile::Mode::Read);
			
			InputStream.seekg(1, std::ios_base::cur);
			read_to(destination);
		};

		void operator>>(std::string& destination)
		{
			SetMode(ByteFile::Mode::Read);

			InputStream.seekg(1, std::ios_base::cur);

			size_t len = read<size_t>();
			if (len > 0)
			{
				char* arr = new char[len]();
				read_to(arr, len);

				destination.assign(arr, len);
			}
		}

		template<typename T>
		T&& read()
		{
			SetMode(ByteFile::Mode::Read);

			T newObject;
			InputStream.read((char*)&newObject, sizeof(T));

			return std::move(newObject);
		}

		bool next_is(Type type)
		{
			SetMode(ByteFile::Mode::Read);

			int next = read<char>();
			InputStream.seekg(-1, std::ios_base::cur);

			return type == (Type)next;
		}

	private:

		template<typename T>
		void write_from(T* buffer, size_t count = 1)
		{
			SetMode(ByteFile::Mode::Write);

			OutputStream.write((char*)buffer, sizeof(T) * count);
		}

		/*
			reads from file to a destination buffer for sizeof(T) x count
		*/
		template<typename T>
		void read_to(T* destination, size_t count = 1)
		{
			SetMode(ByteFile::Mode::Read);

			InputStream.read((char*)destination, sizeof(T) * count);
		}



		std::string Name;

		std::ofstream OutputStream;
		std::ifstream InputStream;

		void SetMode(Mode streamMode);

	};

}