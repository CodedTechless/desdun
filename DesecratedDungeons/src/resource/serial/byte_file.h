#pragma once

/*
	helper class for reading binary files. manages opening/closing for you.
*/

#include <libraries.hpp>

namespace Desdun
{

	class ByteStream
	{
	public:

		void operator>>(std::ofstream& stream)
		{
			
		}

		void operator<<(std::ifstream& stream)
		{

		}

	private:

		char* m_Buffer = nullptr;

		uint m_Size = 0;
		uint m_Reserved = 0;

	};

}