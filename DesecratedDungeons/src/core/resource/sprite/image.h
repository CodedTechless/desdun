#pragma once

#include <libraries.hpp>
#include <core/resource/base/resource.h>


namespace Desdun
{

	struct ImageContext
	{
		const Vector2i Size = {};
		const int BitsPerPixel = 0;
		const std::string& Path = "";
	};

	class Image : public Resource
	{
	public:
		Image() = default;
		Image(const std::string& path);
		~Image();

		void Load(const std::string& path);
		void Push(Vector2i size, int bitsPerPixel, uchar* buffer);

		ImageContext GetContext() const { return { Size, BitsPerPixel, Path }; };
		uchar* GetBuffer() const { return Buffer; };

	private:

		Vector2i Size = {};
		int BitsPerPixel = 0;

		uchar* Buffer = nullptr;
	};

}