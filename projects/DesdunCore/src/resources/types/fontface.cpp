
#include "fontface.hpp"

namespace DesdunCore
{

	FreeTypeLibrary* FontFace::library = nullptr;

	void FontFace::init()
	{
		library = new FreeTypeLibrary();
		if (FT_Init_FreeType(library))
		{
			throw Exception("Failed to initialise FreeTypeLib");
		};
	}

	void FontFace::load()
	{

	}

	void FontFace::unload()
	{

	}


}