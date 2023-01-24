
#include <scene/scene.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtx/compatibility.hpp>

#include "object.h"

namespace Desdun
{

#if 0
	void Object::Serialise(ByteFile& stream) const
	{
		stream << &Position;
		stream << &Scale;
		stream << &Rotation;

		stream << &ZIndex;
		stream << &Visible;

		stream << &Interpolate;

		Instance::Serialise(stream);
	}

	void Object::Deserialise(ByteFile& stream)
	{
		stream >> &Position;
		stream >> &Scale;
		stream >> &Rotation;

		stream >> &ZIndex;
		stream >> &Visible;

		stream >> &Interpolate;

		Instance::Deserialise(stream);
	}

#endif

	void Object::serialise(JSONObject& object) const
	{
		object["position"] = position;
		object["scale"] = scale;
		object["rotation"] = rotation;

		object["zIndex"] = zIndex;
		object["visible"] = visible;

		object["interpolate"] = interpolate;

		Instance::serialise(object);
	}

	void Object::Deserialise(const JSONObject& object)
	{
		object.at("position").get_to(position);
		object.at("scale").get_to(scale);
		object.at("rotation").get_to(rotation);
		
		object.at("zIndex").get_to(zIndex);
		object.at("visible").get_to(visible);

		object.at("interpolate").get_to(interpolate);
		
		Instance::deserialise(object);
	}

	/*
		breaks down the transform into its components, then reconstructs it as an interpolation of Last[component] and [component]
	*/
	Mat4f Object::getInterpTransform() const
	{
		if (interpolate == false)
		{
			return getGlobalTransform();
		}

		Vector2f interpScale = getInterpScale();
		Vector2f interpPos = getInterpPosition();
		float_t interpRot = getInterpRotation();

		Mat4f frame = glm::translate(Mat4f(1.f), Vector3f(interpPos, 0.f))
			* glm::rotate(Mat4f(1.f), interpRot, Vector3f(0.f, 0.f, 1.f))
			* glm::scale(Mat4f(1.f), Vector3f(interpScale, 1.f));

		if (getParent() != nullptr)
		{
			Instance* localSpaceParent = getParent();

			if (localSpaceParent->isA<Object>() == false)
			{
				localSpaceParent = findAncestor<Object>();
			}

			if (localSpaceParent != nullptr)
			{
				frame = ((Object*)localSpaceParent)->getInterpTransform() * frame;
			}
		}

		return frame;
	}

	Vector2f Object::getInterpScale() const
	{
		float_t alpha = Application::get()->getInterpFraction();
		return glm::lerp(LastScale, scale, alpha);
	}

	Vector2f Object::getInterpPosition() const
	{
		float_t alpha = Application::get()->getInterpFraction();
		return glm::lerp(LastPosition, position, alpha);
	}

	float Object::getInterpRotation() const
	{
		float_t alpha = Application::get()->getInterpFraction();
		
		float_t rad = glm::radians(rotation);
		float_t lastrad = glm::radians(LastRotation);

		float_t max = PI * 2.f;
		float_t da = std::fmod(rad - lastrad, max);

		return lastrad + (std::fmod(2 * da, max) - da) * alpha;
	}

	Mat4f Object::getTransform() const
	{
		return glm::translate(Mat4f(1.0f), Vector3f(position, 0.f))
			* glm::rotate(Mat4f(1.0f), glm::radians(rotation), Vector3f(0.f, 0.f, 1.f))
			* glm::scale(Mat4f(1.0f), Vector3f(scale, 1.f));
	}

	Mat4f Object::getGlobalTransform() const
	{
		Mat4f transform = getTransform();

		if (getParent() != nullptr)
		{
			Instance* localSpaceParent = getParent();

			if (localSpaceParent->isA<Object>() == false)
			{
				localSpaceParent = findAncestor<Object>();
			}

			if (localSpaceParent != nullptr)
			{
				transform = ((Object*)localSpaceParent)->getTransform() * transform;
			}
		}

		return transform;
	}

}
