#pragma once

/*
	helper class for reading binary files. manages opening/closing for you.
*/

#include <object/instance.h>

#include <libraries.hpp>

namespace Desdun
{

	using ref_number_t = uint64_t;
	using heap_t = std::unordered_map<byte*, ref_number_t>;

	/*
	takes an class/object/typename/std and turns it in to a binary stream
	this stream can then be written to files and whatnot!
*/

	class ByteStream
	{
	public:
		ByteStream() = default;

		void operator>>(std::ofstream& stream)
		{

		}

		void operator<<(std::ifstream& stream)
		{

		}

	private:

		byte* m_Root = nullptr;

		heap_t m_Heap = {};
		byte* m_Next = 0;

	};

	struct ByteObject
	{
	public:

		ByteObject() = default;

		enum class Type
		{
			Null,
			Pointer,

			Int,
			UnsignedInt,
			Double,
			String,
			Boolean,

			Array,
			Object
		};

		template<typename objectT>
		ByteObject(ByteStream& stream, const objectT& object) : m_Root(&stream)
		{

		}

		template<>
		ByteObject(ByteStream& stream, const std::string& object) : m_Root(&stream)
		{
			m_Buffer = new byte[object.size()];
			m_Size = object.size();

			memcpy_s(m_Buffer, m_Size, object.c_str(), m_Size);
		}

		template<>
		ByteObject(ByteStream& stream, const Vector2& object) : m_Root(&stream)
		{
			m_Buffer = new byte[sizeof(Vector2)];
			m_Size = sizeof(Vector2);
		}

		template<>
		ByteObject(ByteStream& stream, const int64_t& object) : m_Root(&stream)
		{
			m_Buffer = new byte[sizeof(int64_t)];
			m_Size = sizeof(int64_t);
		}

		template<>
		ByteObject(ByteStream& stream, const uint64_t& object) : m_Root(&stream)
		{
			m_Buffer = new byte[sizeof(uint64_t)];
		}

		template<>
		ByteObject(ByteStream& stream, const double_t& object) : m_Root(&stream)
		{
			m_Buffer = new byte[sizeof(double_t)];
		}

		template<>
		ByteObject(ByteStream& stream, const bool& object) : m_Root(&stream)
		{
			m_Buffer = new byte[sizeof(bool)];
		}

		template<typename vectorT = byte>
		ByteObject(ByteStream& stream, const std::vector<vectorT>& vectorArray) : m_Root(&stream)
		{

		}

		/*void resize(size_t newSize)
		{
			if (newSize < m_Size)
			{
				throw Exception("Cannot downsize ByteObject buffer.");
			}

			byte* newBuffer = new byte[newSize];

			memcpy_s(newBuffer, newSize, m_Buffer, m_Size);
			m_Buffer = newBuffer;
		}*/

		const byte* data() const { return m_Buffer; };
		size_t size() const { return m_Size; };

	private:

		Type m_Type = Type::Null;

		byte* m_Buffer = nullptr;
		size_t m_Size = 0;

		ByteStream* m_Root = nullptr;

	};

}