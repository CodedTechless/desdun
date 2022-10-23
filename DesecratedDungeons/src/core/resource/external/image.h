#pragma once

#include <core/resource/base/resource.hpp>
#include <core/graphics/texture/texture_array.h>

#include <libraries.hpp>

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

		void Load(const std::string& path);

		Vector2i GetSize() const { return Size; };
		ImageContext GetContext() const { return { Channels, BitsPerChannel }; };
		uchar* GetBuffer() const { return Buffer; };

		void Allocate(ptr<TextureArray> alloc, uint layer);
		Allocation GetAllocation() { return { TextureAlloc, TextureLayer }; };

	private:

		Enum::ResourceType Type = Enum::ResourceType::Image;

		Vector2i Size = {};
		uchar* Buffer = nullptr;

		int Channels = 0;
		int BitsPerChannel = 8;

		ptr<TextureArray> TextureAlloc = nullptr;
		uint TextureLayer = 0;

	};

}