#pragma once

#include <src/app/resource/resource.hpp>
#include <src/graphics/texture/texture_array.h>

#include <include/desdun_engine.hpp>

namespace Desdun
{

	class AllocationMismatchException : public virtual Exception
	{
	public:
		AllocationMismatchException(Vector2 source, Vector2 dest)
			: Exception(std::format("Image allocation base expected {}x{}, got {}x{}", source.x, source.y, dest.x, dest.y)) {};
	};

	class Image : public Resource
	{
	public:

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

		Vector2i getSize() const;
		uchar* getBuffer() const;
		ImageContext getContext() const;
		Allocation getAllocation() const;

	private:

		Vector2i size = {};
		uchar* buffer = nullptr;

		int channels = 0;
		int bitsPerChannel = 8;

		ptr<TextureArray> textureAlloc = nullptr;
		uint textureLayer = 0;

		void load() override;
		void unload() override;

		void allocate(ptr<TextureArray> alloc);

		friend class Renderer;
		friend class Resource;

	};

}