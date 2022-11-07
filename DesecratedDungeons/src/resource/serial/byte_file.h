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

		void Write(void* Buffer, uint Size);
		void ReadTo(void* Location, uint Size);

		template<typename T>
		T&& Read()
		{
			T object;

			return ReadTo(&object, sizeof(T));
		}

		template<typename T>
		void operator>>(T* ptr)
		{
			ReadTo((void*)ptr, sizeof(T));
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