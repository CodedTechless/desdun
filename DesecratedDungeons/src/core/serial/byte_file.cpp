

#include "byte_file.h"


namespace Desdun
{

	ByteFile::~ByteFile()
	{
		if (InputStream.is_open() == true)
			InputStream.close();

		if (OutputStream.is_open() == true)
			OutputStream.close();
	}

	void ByteFile::Write(void* Buffer, uint Size)
	{
		if (InputStream.is_open() == true)
			InputStream.close();

		if (OutputStream.is_open() == false)
			OutputStream.open(Name, std::ios::binary | std::ios::out);

		OutputStream.write((char*)Buffer, Size);
	}

	void ByteFile::ReadTo(void* Location, uint Size)
	{
		if (OutputStream.is_open() == true)
			OutputStream.close();

		if (InputStream.is_open() == false)
			InputStream.open(Name, std::ios::binary | std::ios::in);

		InputStream.read((char*)Location, Size);
	}

}