#pragma once

#include "font_face.hpp"


namespace DesdunCore
{

	class Font : public Resource
	{
	public:

		void setFontSize(uint size);
		uint getFontSize() const;

		void refresh();
		FontCharacter getCharacter(char character);

	private:

		uint fontSize = 16;
		Dictionary<char, FontCharacter> characters = {};

		void load() override;
		void unload() override;
	};


}