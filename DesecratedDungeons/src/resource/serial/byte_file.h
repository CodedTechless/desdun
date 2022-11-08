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

		enum class ByteType
		{
			Null,
			String,
			Char,
			UnsignedChar,
			Int16,
			UnsignedInt16,
			Int32,
			UnsignedInt32,
			Int64,
			UnsignedInt64,
			Float,
			Double,
			Boolean
		};

		struct BufferByte
		{
			BufferByte(std::ifstream* stream) 
				: InputStream(stream) {};

			ByteType Type = ByteType::Null;

			template<typename T>
			T get()
			{
				return InputStream->read
			}

		private:

			std::ifstream* InputStream;
		};

		void operator>>(char8_t val) { Write((char8_t)ByteType::Char); Write(val); };

		void operator>>(int16_t val) { Write((char8_t)ByteType::Int16); Write(val); };
		void operator>>(int32_t val) { Write((char8_t)ByteType::Int32); Write(val); };
		void operator>>(int64_t val) { Write((char8_t)ByteType::Int64); Write(val); };
		
		void operator>>(uint16_t val) { Write((char8_t)ByteType::UnsignedInt16); Write(val); };
		void operator>>(uint32_t val) { Write((char8_t)ByteType::UnsignedInt32); Write(val); };
		void operator>>(uint64_t val) { Write((char8_t)ByteType::UnsignedInt64); Write(val); };

		void operator>>(float_t val) { Write((char8_t)ByteType::Float); Write(val); };
		void operator>>(double_t val) { Write((char8_t)ByteType::Double); Write(val); };

		void operator>>(bool val) { Write((char8_t)ByteType::Boolean); Write(val); };

		void operator>>(void*) { Write((char8_t)ByteType::Null); };

		BufferByte next()
		{
			BufferByte nextByte(&InputStream);


		}

	private:

		std::string Name;

		std::ofstream OutputStream;
		std::ifstream InputStream;

		void SetMode(Mode streamMode);

		template<typename T>
		void Write(const T& value)
		{
			Write((void*)&value, sizeof(value));
		}

		template<typename T>
		T Read()
		{
			BufferByte newByte;
			Read((void*)&newByte.Type, sizeof(char8_t));

			return newByte.get<T>();
		}

		void Write(void* buffer, size_t bytes);
		void Read(void* location, size_t bytes);

	};

}