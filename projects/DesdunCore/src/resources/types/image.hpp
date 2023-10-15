#pragma once

#include <resources/resource.hpp>
#include <graphics/texture/texture_array.hpp>

#include <corelib/core.hpp>

namespace DesdunCore
{

	class AllocationMismatchException : public virtual Exception
	{
	public:
		AllocationMismatchException(Vector2 source, Vector2 dest)
			: Exception(std::format("Image allocation base expected {}x{}, got {}x{}", source.x, source.y, dest.x, dest.y)) {};
	};

	struct ImageBounds
	{
		Vector2f TL = { 0.f, 0.f };
		Vector2f BR = { 1.f, 1.f };

		friend void to_json(json& object, const ImageBounds& bounds)
		{
			object = json::array({
				bounds.TL,
				bounds.BR
				});
		};

		friend void from_json(const json& object, ImageBounds& bounds)
		{
			bounds = {
				object[0],
				object[1]
			};
		}
	};

	class Image : public Resource
	{
	public:
		Image() = default;
		Image(Vector2 size, uchar* buf = nullptr, uint channels = 4, uint bitsPerChannel = 8);

		struct ImageContext
		{
			int32_t Channels;
			int32_t BitsPerChannel;
		};

		struct Allocation
		{
			Ref<TextureArray> Texture;
			int32_t Layer;
		};

		Vector2i getSize() const;
		uchar* getBuffer() const;
		ImageContext getContext() const;
		Allocation getAllocation() const;

	private:

		Vector2i size = {};
		uchar* buffer = nullptr;

		int32_t channels = 0;
		int32_t bitsPerChannel = 8;

		Ref<TextureArray> textureAlloc = nullptr;
		int32_t textureLayer = 0;

		void load() override;
		void unload() override;

		void allocate(Ref<TextureArray> alloc);

		friend class Renderer;
		friend class Resource;

	};

}