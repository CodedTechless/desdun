#pragma once

#include <app/app.hpp>
#include <resources/resource.hpp>

namespace DesdunCore
{

	struct FontCharacter
	{
		Image* image;
		Vector2 size;
		Vector2 bearing;
		uint advance;
	};

	class FontFace : public Resource
	{
	public:
		static void init();

		void getGlyphs(uint size, Dictionary<char, FontCharacter>& characters);

	private:
		void load() override;
		void unload() override;

		FT_Face face;
		
	private:
		static FT_Library* library;

		friend class Application;
	};

}