#pragma once

/*
	helper class for reading binary files. manages opening/closing for you.
*/

#include <object/instance.h>

#include <core_lib.hpp>

namespace Desdun
{

#if 0
	using ref_number_t = uint64_t;
	using heap_t = std::unordered_map<byte*, ref_number_t>;

	/*
	takes an class/object/typename/std and turns it in to a binary stream
	this stream can then be written to files and whatnot!
*/

	class BytePrimitive
	{
	public:
		BytePrimitive() = default;

		enum class Type
		{
			Null,
			Reference,

			Int,
			UnsignedInt,
			Double,
			String,
			Boolean,

			Vector2,

			Array,
			Map,
			Object
		};

		BytePrimitive(const String& object) : m_Type(Type::String)
		{
			allocate(object.size() * sizeof(wchar_t));

			memcpy_s(m_Buffer, m_Size, object.c_str(), m_Size);
		}

		BytePrimitive(const Vector2& object) : m_Type(Type::Vector2)
		{
			allocate<Vector2>();
		}

		BytePrimitive(const int64_t& object) : m_Type(Type::Int)
		{
			allocate<int64_t>();
		}

		BytePrimitive(const uint64_t& object) : m_Type(Type::UnsignedInt)
		{
			allocate<uint64_t>();
		}

		BytePrimitive(const double_t& object) : m_Type(Type::Double)
		{
			allocate<double_t>();
		}

		BytePrimitive(const bool& object) : m_Type(Type::Boolean)
		{
			allocate<bool>();
		}

		template<typename vectorT>
		BytePrimitive() : m_Type(Type::Array)
		{
			allocate(object.size() * sizeof(vectorT));
		}

		template<typename keyT, typename valueT>
		BytePrimitive() : m_Type(Type::Map)
		{
			
		}

		template<typename pointerT>
		BytePrimitive(pointerT* pointer) : m_Type(Type::Reference)
		{
			m_Type = Type::Reference;
			m_Buffer = (byte*)pointer;
		}

		const Type type() const { return m_Type; };
		byte* data() const { return m_Buffer; };
		size_t size() const { return m_Size; };

	protected:

		template<typename T>
		void allocate()
		{
			m_Buffer = new byte[sizeof(T)];
			m_Size = sizeof(T);
		};

		void allocate(uint size)
		{
			m_Buffer = new byte[size];
			m_Size = size;
		};


		Type m_Type = Type::Null;

		byte* m_Buffer = nullptr;
		size_t m_Size = 0;

	};

	class ByteStream;

	class ByteObject : public BytePrimitive
	{
	public:

		template<typename keyT, typename valueT>
		ByteObject(ByteStream* owner, const std::unordered_map<keyT, valueT>& object)
		{

		}

		template<typename valueT>
		ByteObject(ByteStream* owner, const std::vector<valueT>& object)
		{

		}

		ByteObject(ByteStream* owner, const BaseRuntimeClass& runtimeClass)
		{
			m_MaxSize = 16;
			m_Buffer = new byte[m_MaxSize];
			
			m_Type = Type::Object;
			push((char)Type::Object);
		}

		void operator<<(const BytePrimitive& primitive)
		{
			push((char)primitive.type());

			switch (primitive.type())
			{
				case Type::Reference: 
				{
					push(m_StreamOwner->getObjectRefID(primitive.data()));
					break;
				};
				default:
				{
					push(primitive.data(), primitive.size());
				}
			}
			
			
		}

		

	private:

		/*
			for pushing a value in to the buffer and resizing the buffer if it isn't big enough
		*/
		template<typename T>
		void push(const T& value, size_t size = sizeof(T))
		{
			push(&value, size);
		}

		template<typename T>
		void push(T* value, size_t size)
		{
			if (m_Size + size * 2 > m_MaxSize)
			{
				byte* oldStream = m_Buffer; // get the old buffer

				m_Buffer = new byte[m_MaxSize * 2](); // create a new buffer with double the max size
				memcpy_s(m_Buffer, m_MaxSize * 2, oldStream, m_Size); // copy oldStream and its data into the new buffer

				m_MaxSize *= 2; // apply the size change
				delete oldStream; // delete the old buffer
			}

			memcpy_s(m_Buffer + size, m_MaxSize - m_Size, value, size);
			m_Size += size;
		}

		ByteStream* m_StreamOwner;
		size_t m_MaxSize = 16;

	};

	class ByteStream
	{
	public:
		

		void operator>>(std::ofstream& stream)
		{

		}

		void operator<<(std::ifstream& stream)
		{

		}

		template<typename T>
		void operator<<(T* object)
		{
			ByteObject byteObject(this, object->GetClassIndex());

			object->Serialise(byteObject);
		}

		ref_number_t getObjectRefID(byte* pointer)
		{
			auto it = m_Heap.find(pointer);
			if (it != m_Heap.end())
			{
				return it->second;
			}

			m_Heap[pointer] = ++m_NextRef;
			return m_NextRef;
		}

	private:

		Instance* m_Root = nullptr;

		heap_t m_Heap = {};
		ref_number_t m_NextRef = 0;

	};


#endif


}