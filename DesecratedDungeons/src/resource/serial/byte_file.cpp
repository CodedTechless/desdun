

#include "byte_file.h"


namespace Desdun
{
	
	ByteOutputStream::ByteOutputStream(const std::string& name)
		: m_Name(name)
	{
		m_Stream.open(name, std::ios_base::binary | std::ios_base::out);
	}

	ByteInputStream::ByteInputStream(const std::string& name)
		: m_Name(name)
	{
		m_Stream.open(name, std::ios_base::binary | std::ios_base::in);
	}

	ByteOutputStream::~ByteOutputStream()
	{
		if (m_Stream.is_open() == true)
			m_Stream.close();
	}

	ByteInputStream::~ByteInputStream()
	{
		if (m_Stream.is_open() == true)
			m_Stream.close();
	}

}