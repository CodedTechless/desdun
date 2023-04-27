
#include <scene/scene.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtx/compatibility.hpp>

#include "object.h"

namespace Desdun
{

	void WorldObject::serialise(JSONObject& object) const
	{
		object["position"] = position;
		object["scale"] = scale;
		object["rotation"] = rotation;

		object["zIndex"] = zIndex;
		object["visible"] = visible;

		object["interpolate"] = interpolate;

		Instance::serialise(object);
	}

	void WorldObject::deserialise(const JSONObject& object)
	{
		object.at("position").get_to(position);
		object.at("scale").get_to(scale);
		object.at("rotation").get_to(rotation);
		
		object.at("zIndex").get_to(zIndex);
		object.at("visible").get_to(visible);

		object.at("interpolate").get_to(interpolate);
		
		Instance::deserialise(object);
	}

	void WorldObject::checkDirty()
	{
		if (position != positionLast or scale != scaleLast or rotation != rotationLast)
		{
			markDirty();
		}
	}

	void WorldObject::markDirty()
	{
		dirtyGlobal = true;
		Instance::markDirty();
	}

	void WorldObject::markInterpDirty()
	{
		dirtyInterp = true;
	}

	void WorldObject::ageLocalTransform()
	{
		positionLast = position;
		scaleLast = scale;
		rotationLast = rotation;
	}

	void WorldObject::bakeGlobalTransform()
	{
		if (not dirtyGlobal)
			return;

		auto* ancestor = findAncestorOfType<WorldObject>();
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

	void WorldObject::bakeInterpolatedTransform()
	{
		// TODO - remove unnecessary interpolation calc

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

		WorldObject* ancestor = findAncestorOfType<WorldObject>();
		if (ancestor)
		{
			transformLocal = ancestor->getRenderTransform() * transformLocal;
		}

		transformRender = transformLocal;

		dirtyInterp = false;
	}

	Mat4f WorldObject::getGlobalTransform()
	{
		bakeGlobalTransform();
		return transformGlobal;
	}

	void WorldObject::setPosition(const Vector2f& newPos)
	{
		position = newPos;
		checkDirty();
	}

	void WorldObject::setScale(const Vector2f& newScale)
	{
		scale = newScale;
		checkDirty();
	}

	void WorldObject::setRotation(float_t newRot)
	{
		rotation = newRot;
		checkDirty();
	}

	void WorldObject::translate(const Vector2f& translation)
	{
		position += translation;
		checkDirty();
	}

	void WorldObject::resize(const Vector2f& size)
	{
		scale += size;
	}

	void WorldObject::rotate(float_t rotationAmount)
	{
		rotation = std::fmod(rotation + rotationAmount, math::PI2);
		checkDirty();
	}

	Vector2f WorldObject::getPosition() const
	{
		return position;
	}

	Vector2f WorldObject::getScale() const
	{
		return scale;
	}

	float_t WorldObject::getRotation() const
	{
		return rotation;
	}

	Vector2f WorldObject::getGlobalPosition()
	{
		bakeGlobalTransform();
		return positionGlobal;
	}

	Vector2f WorldObject::getGlobalScale()
	{
		bakeGlobalTransform();
		return scaleGlobal;
	}

	float_t WorldObject::getGlobalRotation()
	{
		bakeGlobalTransform();
		return rotationGlobal;
	}

	Mat4f WorldObject::getRenderTransform()
	{
		bakeInterpolatedTransform();
		return transformRender;
	}

	Vector2f WorldObject::getLocalInterpPosition()
	{
		bakeInterpolatedTransform();
		return positionGlobal;
	}

	Vector2f WorldObject::getLocalInterpScale()
	{
		bakeInterpolatedTransform();
		return scaleInterp;
	}

	float_t WorldObject::getLocalInterpRotation()
	{
		bakeInterpolatedTransform();
		return rotationInterp;
	}
}
