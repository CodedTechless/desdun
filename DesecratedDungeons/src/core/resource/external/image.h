#pragma once

#include <libraries.hpp>
#include <core/resource/base/resource.hpp>


namespace Desdun
{

	struct ImageContext
	{
		const int Channels;
		const int BitsPerChannel;
	};

	class Image : public Resource
	{
	public:

		Image() = default;
		~Image();

		void Load(const std::string& path);

		Vector2i GetSize() const { return Size; };
		ImageContext GetContext() const { return { Channels, BitsPerChannel }; };
		uchar* GetBuffer() const { return Buffer; };

	private:

		Enum::ResourceType Type = Enum::ResourceType::Image;

		Vector2i Size = {};
		int Channels = 0;
		int BitsPerChannel = 8;

		uchar* Buffer = nullptr;

		ptr<TextureArray> TextureAlloc = nullptr;
		uint TextureLayer = 0;

	};

}