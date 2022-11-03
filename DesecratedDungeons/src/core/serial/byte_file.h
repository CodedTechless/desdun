#pragma once

#include <libraries.hpp>


namespace Desdun
{

	class ByteFile
	{
	public:
		ByteFile() = default;
		~ByteFile();

		void Open(const std::string& Name);

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

		void Close();

	private:

		std::ofstream OutputStream;
		std::ifstream InputStream;
	};

}