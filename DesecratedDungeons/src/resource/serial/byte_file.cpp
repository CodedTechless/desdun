

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

	void ByteFile::SetMode(Mode bufferMode)
	{
		if (bufferMode == Mode::Write)
		{
			if (InputStream.is_open() == true)
				InputStream.close();

			if (OutputStream.is_open() == false)
				OutputStream.open(Name, std::ios::binary | std::ios::out);
		}
		else if (bufferMode == Mode::Read)
		{
			if (OutputStream.is_open() == true)
				OutputStream.close();

			if (InputStream.is_open() == false)
				InputStream.open(Name, std::ios::binary | std::ios::in);
		}
	}
}