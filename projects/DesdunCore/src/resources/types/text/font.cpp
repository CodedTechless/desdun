

#include "font.hpp"

namespace DesdunCore
{

	void Font::setFontSize(uint size)
	{
		fontSize = size;
		refresh();
	}

	uint Font::getFontSize() const
	{
		return fontSize;
	}
	
	FontCharacter Font::getCharacter(char character)
	{
		return characters[character];
	}

	void Font::refresh()
	{
		json res = loadAsJSON();
		String fontLocation = res.at("fontFace").get<String>();
		
		characters.clear();

		FontFace* face = Resource::fetch<FontFace>(fontLocation);
		face->getGlyphs(fontSize, characters);
	}

	void Font::load()
	{
		try
		{
			refresh();
		}
		catch(Exception err)
		{
			throw err;
		}
	}

	void Font::unload()
	{
		for (auto& [character, fontCharacter] : characters)
		{
			delete fontCharacter.image;
		}
	}

}