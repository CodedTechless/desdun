#pragma once

#include <core/resource/base/resource.h>
#include <core/graphics/texture/texture_array.h>

namespace Desdun
{

	struct SpriteBounds
	{
		Vector2 A = { 0.f, 0.f };
		Vector2 B = { 1.f, 1.f };
	};

	class Sprite : public Resource
	{
	public:

		Sprite() = default;

		void Load(const std::string& path);
		void SetTexture(ptr<TextureArray> image, const SpriteBounds& bounds, uint layer);

	private:

		ptr<TextureArray> m_Texture = nullptr;
		SpriteBounds m_Bounds = {};

		uint m_Layer = 0;

	};

}