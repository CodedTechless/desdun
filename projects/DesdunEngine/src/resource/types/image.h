#pragma once

#include <resource/resource.hpp>
#include <graphics/texture/texture_array.h>

#include <core_lib.hpp>

namespace Desdun
{

	class Image : public Resource
	{
	public:

		Image() = default;
		~Image();

		struct ImageContext
		{
			const int Channels;
			const int BitsPerChannel;
		};

		struct Allocation
		{
			ptr<TextureArray> Texture;
			uint Layer;
		};

		void load(const std::string& path) override;

		Vector2i GetSize() const { return Size; };
		ImageContext GetContext() const { return { Channels, BitsPerChannel }; };
		uchar* GetBuffer() const { return Buffer; };

		void Allocate(ptr<TextureArray> alloc);
		Allocation GetAllocation() { return { TextureAlloc, TextureLayer }; };

	private:

		Vector2i Size = {};
		uchar* Buffer = nullptr;

		int Channels = 0;
		int BitsPerChannel = 8;

		ptr<TextureArray> TextureAlloc = nullptr;
		uint TextureLayer = 0;

		friend class Renderer;

	};

}