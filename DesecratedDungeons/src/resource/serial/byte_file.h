#pragma once

/*
	helper class for reading binary files. manages opening/closing for you.
*/

#include <object/instance.h>

#include <libraries.hpp>

namespace Desdun
{

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

		struct ByteItem
		{
		public:

			template<typename objectT>
			ByteItem(const objectT& object)
			{

			}

			template<>
			ByteItem(const std::string& object)
			{
				m_Buffer = new char[object.size()];
				m_Size = object.size();

				memcpy_s(m_Buffer, m_Size, object.c_str(), m_Size);
			}

			template<>
			ByteItem(const Vector2& object)
			{
				m_Buffer = new char[sizeof(Vector2)];
				m_Size = sizeof(Vector2);
			}

			template<>
			ByteItem(const int64_t& object)
			{
				m_Buffer = new char[sizeof(int64_t)];
				m_Size = sizeof(int64_t);
			}

			template<>
			ByteItem(const uint64_t& object)
			{
				m_Buffer = new char[sizeof(uint64_t)];
			}

			template<>
			ByteItem(const double_t& object)
			{
				m_Buffer = new char[sizeof(double_t)];
			}

			template<>
			ByteItem(const bool& object)
			{
				m_Buffer = new char[sizeof(bool)];
			}

			template<typename pointerRawT = char>
			ByteItem(pointerRawT* pointer)
			{

			}

			template<typename arrayRawT = char>
			ByteItem(arrayRawT* pointer, size_t count)
			{

			}

			template<typename vectorT = char>
			ByteItem(const std::vector<vectorT>& vectorArray)
			{

			}

			void resize(size_t newSize)
			{
				if (newSize < m_Size)
				{
					throw Exception("Cannot downsize item buffer");
				}

				char* newBuffer = new char[newSize];

				memcpy_s(newBuffer, newSize, m_Buffer, m_Size);
				m_Buffer = newBuffer;
			}

			const char* GetBuffer() const { return m_Buffer; };
			size_t GetSize() const { return m_Size; };

		private:

			char* m_Buffer;
			size_t m_Size;

			std::vector<ByteItem> m_ContainedItems = {};

		};

	private:
		
		using pointer_t = unsigned int;
		using buffer_object_t = std::unordered_map<pointer_t, ByteItem>;

	private:

		char* m_Root = nullptr;

		buffer_object_t m_BufferArray = {};
		pointer_t m_Next = 0;

	};

}