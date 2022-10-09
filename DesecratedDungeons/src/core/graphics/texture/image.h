#pragma once

#include <libraries.hpp>


namespace Desdun
{

	struct ImageContext
	{
		const Vector2i Size = {};
		const int BitsPerPixel = 0;
		const std::string& Path = "";
	};

	class Image
	{
	public:
		Image() = default;
		Image(const std::string& FilePath);
		Image(Vector2i size, int bitsPerPixel, uchar* buffer);
		~Image();

		ImageContext GetContext() const { return { Size, BitsPerPixel, Path }; };
		uchar* GetBuffer() const { return Buffer; };

	private:
		std::string Path = "";

		Vector2i Size = {};
		int BitsPerPixel = 0;

		uchar* Buffer = nullptr;
	};

}