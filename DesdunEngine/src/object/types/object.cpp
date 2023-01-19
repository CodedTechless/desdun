
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

	void Object::Serialise(JSONObject& object) const
	{
		object["Position"] = Position;
		object["Scale"] = Scale;
		object["Rotation"] = Rotation;

		object["ZIndex"] = ZIndex;
		object["Visible"] = Visible;

		object["Interpolate"] = Interpolate;

		Instance::Serialise(object);
	}

	void Object::Deserialise(const JSONObject& object)
	{
		object.at("Position").get_to(Position);
		object.at("Scale").get_to(Scale);
		object.at("Rotation").get_to(Rotation);
		
		object.at("ZIndex").get_to(ZIndex);
		object.at("Visible").get_to(Visible);

		object.at("Interpolate").get_to(Interpolate);
		
		Instance::Deserialise(object);
	}

	/*
		breaks down the transform into its components, then reconstructs it as an interpolation of Last[component] and [component]
	*/
	Mat4f Object::GetInterpTransform() const
	{
		if (Interpolate == false)
		{
			return GetGlobalTransform();
		}

		float_t alpha = Application::GetApplication()->GetInterpolationFraction();

		// scale
		Vector2f scale = glm::lerp(LastScale, Scale, alpha);

		// rotation
		float_t rad = glm::radians(Rotation);
		float_t lastrad = glm::radians(LastRotation);

		float_t max = PI * 2.f;
		float_t da = std::fmod(rad - lastrad, max);

		float_t rot = lastrad + (std::fmod(2 * da, max) - da) * alpha;

		// position
		Vector2f pos = glm::lerp(LastPosition, Position, alpha) * scale;

		Mat4f frame = glm::translate(Mat4f(1.f), Vector3f(pos, 0.f))
			* glm::rotate(Mat4f(1.f), rot, Vector3f(0.f, 0.f, 1.f))
			* glm::scale(Mat4f(1.f), Vector3f(scale, 1.f));

		if (GetParent() != nullptr)
		{
			Instance* localSpaceParent = GetParent();

			if (localSpaceParent->IsA<Object>() == false)
			{
				localSpaceParent = FindAncestor<Object>();
			}

			if (localSpaceParent != nullptr)
			{
				frame = ((Object*)localSpaceParent)->GetInterpTransform() * frame;
			}
		}

		return frame;
	}

	Mat4f Object::GetTransform() const
	{
		return glm::translate(Mat4f(1.0f), Vector3f(Position, 0.f))
			* glm::rotate(Mat4f(1.0f), glm::radians(Rotation), Vector3f(0.f, 0.f, 1.f))
			* glm::scale(Mat4f(1.0f), Vector3f(Scale, 1.f));
	}

	Mat4f Object::GetGlobalTransform() const
	{
		Mat4f transform = GetTransform();

		if (GetParent() != nullptr)
		{
			Instance* localSpaceParent = GetParent();

			if (localSpaceParent->IsA<Object>() == false)
			{
				localSpaceParent = FindAncestor<Object>();
			}

			if (localSpaceParent != nullptr)
			{
				transform = ((Object*)localSpaceParent)->GetTransform() * transform;
			}
		}

		return transform;
	}

}
