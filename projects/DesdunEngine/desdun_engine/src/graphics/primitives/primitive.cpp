
#include <desdun_engine/src/graphics/render/renderer.h>
#include <desdun_engine/src/app/resource/resource.hpp>
#include <desdun_engine/src/app/app.h>

#include "primitive.h"

namespace Desdun
{

	void Primitive::drawRect(Vector2 position, Vector2 size, float zIndex, float rotation, Color4 tint)
	{
		auto* image = Resource::fetch<Image>("textures:dev/white.png");

		Mat4f transform = glm::translate(Mat4(1.f), Vector3f(position, 1.f))
			* glm::scale(Mat4f(1.f), Vector3f(Vector2f(image->getSize()), 1.f))
			* glm::rotate(Mat4f(1.f), rotation, Vector3f(1.f, 1.f, 1.f));

		auto* app = Application::get();
		app->getRenderer()->enqueue({ 
			transform, tint, 
			{ 
				{0.f, 0.f}, 
				{ 1.f, 1.f }
			}, 
			image, nullptr, zIndex 
		});
	}

}