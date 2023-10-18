#pragma once

#include <objects/types/2d/entity.hpp>

#include <graphics/render/renderer.hpp>

namespace DesdunCore
{
	class Sprite : public Entity2D
	{
	public:
		dd_serialisable(Sprite)

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