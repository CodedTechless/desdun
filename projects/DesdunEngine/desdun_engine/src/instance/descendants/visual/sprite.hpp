#pragma once

#include <src/instance/descendants/object.h>

#include <src/graphics/render/renderer.h>

namespace Desdun
{
	class Sprite : public WorldObject
	{
	public:
		serialisable(Sprite)

		Image* image = nullptr;
		Shader* shader = nullptr;

		Color4f tint = { 1.f, 1.f, 1.f, 1.f };
		Vector2f tiles = { 1.f, 1.f };
		Vector2f offset = { 0.f, 0.f };

		ImageBounds bounds = {
			{ 0.f, 0.f },
			{ 1.f, 1.f }
		};

		void onFrameUpdate(const float_t delta) override;

	protected:

		void serialise(JSONObject& object) const override;
		void deserialise(const JSONObject& object) override;

	};
}