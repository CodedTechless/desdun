#pragma once

#include <libraries.hpp>


namespace Desdun
{

	struct ImageContext
	{
		Vector2i Size = {};
		int BitsPerPixel = 0;
	};

	class Image
	{
	public:
		Image() = default;
		~Image();

		static ptr<Image> Create(const std::string& FilePath);
		static ptr<Image> Create(Vector2i size, int bitsPerPixel, uchar* buffer);

		ImageContext GetContext() const { return { Size, BitsPerPixel }; };
		uchar* GetBuffer() const { return Buffer; };

	private:
		std::string Path = "";

		Vector2i Size = {};
		int BitsPerPixel = 0;

		uchar* Buffer = nullptr;
	};

}