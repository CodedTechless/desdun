
#include <graphics/renderer.h>
#include <resource/resource.hpp>

#include "primitive.h"

namespace Desdun
{

	void Primitive::drawRect(Vector2 position, Vector2 size, float zIndex, float rotation, Color4 tint)
	{
		auto* image = Resource::fetch<Image>("textures:dev/white.png");

		Mat4f transform = glm::translate(Mat4(1.f), Vector3f(position, 1.f))
			* glm::scale(Mat4f(1.f), Vector3f(Vector2f(image->getSize()), 1.f))
			* glm::rotate(Mat4f(1.f), rotation, Vector3f(1.f, 1.f, 1.f));

		Renderer::Submit({ transform, tint, { {0.f, 0.f}, { 1.f, 1.f } }, image, nullptr, zIndex });
	}

}