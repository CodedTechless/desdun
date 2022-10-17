#pragma once

#include <libraries.hpp>
#include <core/resource/base/resource.hpp>


namespace Desdun
{

	struct ImageContext
	{
		const Vector2i Size;
		const int BitsPerPixel;
	};

	class Image : public Resource
	{
	public:
		Image() = default;
		~Image();

		void Load(const std::string& path);
//		void Push(Vector2i size, int bitsPerPixel, uchar* buffer);

		ImageContext GetContext() const { return { Size, BitsPerPixel }; };
		uchar* GetBuffer() const { return Buffer; };

	private:

		Vector2i Size = {};
		int BitsPerPixel = 0;

		uchar* Buffer = nullptr;
	};

}