#pragma once

#include <libraries.hpp>


namespace Desdun
{

	class ByteFile
	{
	public:
		ByteFile(const std::string& name)
			: Name(name) {};

		~ByteFile();

		void Write(void* Buffer, size_t Size);
		void ReadTo(void* Location, uint Size);

		template<typename T>
		T&& Read(uint count = 1)
		{
			T object;

			return ReadTo(&object, sizeof(T) * count);
		}

		template<typename T>
		void operator>>(T* ptr)
		{
			ReadTo((void*)ptr, sizeof(T));
		}

		void operator>>(std::string& ptr)
		{
			size_t length = Read<size_t>();
			char* arr = new char[length]();
			ReadTo((void*)arr, length);

			ptr.assign(arr, length);
		}

		void operator<<(const std::string& str)
		{
			const char* arr = str.c_str();
			size_t size = str.size();

			Write((void*)&size, sizeof(size_t));
			Write((void*)arr, size);
		}

		template<typename T>
		void operator<<(T* ptr)
		{
			Write((void*)ptr, sizeof(T));
		}

		template<typename T>
		void operator<<(T var)
		{
			Write((void*)&var, sizeof(T));
		}

	private:

		std::string Name;

		std::ofstream OutputStream;
		std::ifstream InputStream;

	};

}