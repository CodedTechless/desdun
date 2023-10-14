#pragma once

#include <app/app.hpp>
#include <resources/resource.hpp>

namespace DesdunCore
{

	using FreeTypeLibrary = FT_Library;

	class FontFace : public Resource
	{
	public:

		static void init();

	protected:
		void load() override;
		void unload() override;

	private:

		static FreeTypeLibrary* library;

		friend class Application;
	};

}