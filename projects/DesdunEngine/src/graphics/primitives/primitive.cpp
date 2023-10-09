
#include <src/graphics/render/renderer.h>
#include <src/resources/resource.hpp>
#include <src/app/app.h>

#include "primitive.h"

namespace Desdun
{

	void Primitive::drawRect(Vector2 position, Vector2 size, float zIndex, float rotation, Color4 tint)
	{
		auto* image = Resource::fetch<Image>("textures:dev/white.png");

		Mat4f transform = glm::translate(Mat4(1.f), Vector3f(position, 1.f))
			* glm::rotate(Mat4f(1.f), rotation, Vector3f(0.f, 0.f, 1.f))
			* glm::scale(Mat4f(1.f), Vector3f(size, 1.f));

		Renderer::Command command;
		command.transform = transform;
		command.tint = tint;
		command.image = image;
		command.zIndex = zIndex;

		auto* app = Application::get();
		app->getRenderer()->enqueue(command);
	}

	void Primitive::drawLine(const Vector2& p0, const Vector2& p1, const Color4f tint)
	{
		auto* image = Resource::fetch<Image>("textures:dev/white.png");

		Vector2f diff = (p1 - p0);
		Vector2f p = p0 + (diff / 2.f);

		Mat4f transform = glm::translate(Mat4(1.f), Vector3f(p, 1.f))
			* glm::rotate(Mat4f(1.f), std::atan2(diff.y, diff.x) + math::PI / 2, Vector3f(0.f, 0.f, 1.f))
			* glm::scale(Mat4f(1.f), Vector3f(Vector2f(1.f, glm::length(diff)), 1.f));

		Renderer::Command command;
		command.transform = transform;
		command.tint = tint;
		command.image = image;
		command.zIndex = 10000.f;

		auto* app = Application::get();
		app->getRenderer()->enqueue(command);
	}

}