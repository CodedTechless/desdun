
#include <runtime/scene/scene.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtx/compatibility.hpp>

#include "entity.hpp"

namespace DesdunCore
{

	void Entity2D::serialise(JSONObject& object) const
	{
		object["position"] = position;
		object["scale"] = scale;
		object["rotation"] = rotation;

		object["zIndex"] = zIndex;
		object["visible"] = visible;

		object["interpolate"] = interpolate;

		Object::serialise(object);
	}

	void Entity2D::deserialise(const JSONObject& object)
	{
		object.at("position").get_to(position);
		object.at("scale").get_to(scale);
		object.at("rotation").get_to(rotation);
		
		object.at("zIndex").get_to(zIndex);
		object.at("visible").get_to(visible);

		object.at("interpolate").get_to(interpolate);
		
		Object::deserialise(object);
	}

	void Entity2D::checkDirty()
	{
		if (position != positionLast or scale != scaleLast or rotation != rotationLast)
		{
			markDirty();
		}
	}

	void Entity2D::markDirty()
	{
		dirtyGlobal = true;
		Object::markDirty();
	}

	void Entity2D::markInterpDirty()
	{
		dirtyInterp = true;
	}

	void Entity2D::ageLocalTransform()
	{
		positionLast = position;
		scaleLast = scale;
		rotationLast = rotation;
	}

	void Entity2D::bakeGlobalTransform()
	{
		if (not dirtyGlobal)
			return;

		auto* ancestor = findAncestorOfType<Entity2D>();
		if (ancestor)
		{
			ancestor->bakeGlobalTransform();

			scaleGlobal = scale * ancestor->scaleGlobal;
			rotationGlobal = ancestor->rotationGlobal + rotation;

			float_t s = std::sin(ancestor->rotationGlobal);
			float_t c = std::cos(ancestor->rotationGlobal);

			positionGlobal = ancestor->positionGlobal;
			positionGlobal += ancestor->scaleGlobal * Vector2f(position.x * c - position.y * s, position.x * s + position.y * c);
		}
		else
		{
			positionGlobal = position;
			scaleGlobal = scale;
			rotationGlobal = rotation;
		}

		transformGlobal = glm::translate(Mat4f(1.f), Vector3f(positionGlobal, 0.f))
			* glm::rotate(Mat4f(1.f), rotationGlobal, Vector3f(0.f, 0.f, 1.f))
			* glm::scale(Mat4f(1.f), Vector3f(scaleGlobal, 1.f));

		dirtyGlobal = false;
	}

	void Entity2D::bakeInterpolatedTransform()
	{
		// TODO: remove unnecessary interpolation calc

		if (not dirtyInterp)
		{
			return;
		}

		if (interpolate)
		{
			float_t factor = Application::get()->getInterpFraction();

			positionInterp = glm::lerp(positionLast, position, factor);
			scaleInterp = glm::lerp(scaleLast, scale, factor);
			rotationInterp = math::rlerp(rotationLast, rotation, factor);
		}
		else
		{
			positionInterp = position;
			scaleInterp = scale;
			rotationInterp = rotation;
		}

		Mat4f transformLocal = glm::translate(Mat4f(1.f), Vector3f(positionInterp, 0.f))
			* glm::rotate(Mat4f(1.f), rotationInterp, Vector3f(0.f, 0.f, 1.f))
			* glm::scale(Mat4f(1.f), Vector3f(scaleInterp, 1.f));

		Entity2D* ancestor = findAncestorOfType<Entity2D>();
		if (ancestor)
		{
			transformLocal = ancestor->getRenderTransform() * transformLocal;
		}

		transformRender = transformLocal;

		dirtyInterp = false;
	}

	Mat4f Entity2D::getGlobalTransform()
	{
		bakeGlobalTransform();
		return transformGlobal;
	}

	void Entity2D::setPosition(const Vector2f& newPos)
	{
		position = newPos;
		checkDirty();
	}

	void Entity2D::setScale(const Vector2f& newScale)
	{
		scale = newScale;
		checkDirty();
	}

	void Entity2D::setRotation(float_t newRot)
	{
		rotation = newRot;
		checkDirty();
	}

	void Entity2D::translate(const Vector2f& translation)
	{
		position += translation;
		checkDirty();
	}

	void Entity2D::resize(const Vector2f& size)
	{
		scale += size;
	}

	void Entity2D::rotate(float_t rotationAmount)
	{
		rotation = std::fmod(rotation + rotationAmount, math::PI2);
		checkDirty();
	}

	Vector2f Entity2D::getPosition() const
	{
		return position;
	}

	Vector2f Entity2D::getScale() const
	{
		return scale;
	}

	float_t Entity2D::getRotation() const
	{
		return rotation;
	}

	Vector2f Entity2D::getGlobalPosition()
	{
		bakeGlobalTransform();
		return positionGlobal;
	}

	Vector2f Entity2D::getGlobalScale()
	{
		bakeGlobalTransform();
		return scaleGlobal;
	}

	float_t Entity2D::getGlobalRotation()
	{
		bakeGlobalTransform();
		return rotationGlobal;
	}

	Mat4f Entity2D::getRenderTransform()
	{
		bakeInterpolatedTransform();
		return transformRender;
	}

	Vector2f Entity2D::getLocalInterpPosition()
	{
		bakeInterpolatedTransform();
		return positionGlobal;
	}

	Vector2f Entity2D::getLocalInterpScale()
	{
		bakeInterpolatedTransform();
		return scaleInterp;
	}

	float_t Entity2D::getLocalInterpRotation()
	{
		bakeInterpolatedTransform();
		return rotationInterp;
	}
}
