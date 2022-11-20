#pragma once

/*
	helper class for reading binary files. manages opening/closing for you.
*/

#include <libraries.hpp>

namespace Desdun
{

	namespace ByteStream
	{
		enum class Type
		{
			Null,
			Int,
			UnsignedInt,
			Double,
			Bool,
			String
		};
	};

	class ByteOutputStream
	{
	public:
		ByteOutputStream(const std::string& name);
		~ByteOutputStream();

		template<typename T>
		void write(ByteStream::Type type, T* buffer = nullptr)
		{
			char typeFinal = static_cast<char>(type);

			m_Stream.write((char*)&typeFinal, sizeof(char));

			if (buffer)
			{
				m_Stream.write((char*)buffer, sizeof(T));
			}
		};

		template<typename T>
		void write(T* buffer, size_t count)
		{
			m_Stream.write((char*)buffer, sizeof(T) * count);
		};

		void operator<<(const int64_t& source) 
		{
			write(ByteStream::Type::Int, &source);
		};

		void operator<<(const uint64_t& source)
		{
			write(ByteStream::Type::UnsignedInt, &source);
		};

		void operator<<(const std::string& source)
		{
			size_t count = source.size();

			write(ByteStream::Type::String, &count);
			write(source.c_str(), count);
		}

	private:

		std::string m_Name;
		std::ofstream m_Stream;

	};

	class ByteInputStream
	{
	public:
		ByteInputStream(const std::string& name)
			: m_Name(name) {};

		~ByteInputStream();



	private:

		std::string m_Name;
		std::ifstream m_Stream;

	};

}