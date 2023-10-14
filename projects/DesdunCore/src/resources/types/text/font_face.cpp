
#include "font_face.hpp"

namespace DesdunCore
{

	FT_Library* FontFace::library = nullptr;

	void FontFace::init()
	{
		library = new FT_Library();
		if (FT_Init_FreeType(library))
		{
			throw Exception("Failed to initialise FreeTypeLib");
		};
	}

	void FontFace::getGlyphs(const uint fontSize, Dictionary<char, FontCharacter>& characters)
	{
		FT_Set_Pixel_Sizes(face, 0, fontSize);
	}

	void FontFace::load()
	{
		if (FT_New_Face(*library, getPath().c_str(), 0, &face))
		{
			throw Exception(std::format("Cannot load font {}", getPath()));
		}
	}

	void FontFace::unload()
	{
		FT_Done_Face(face);
	}


}