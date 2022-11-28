
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

	}

	/*
		breaks down the transform into its components, then reconstructs it as an interpolation of Last[component] and [component]
	*/
	Mat4 Object::GetInterpTransform() const
	{
		if (Interpolate == false)
		{
			return GetGlobalTransform();
		}

		double_t alpha = Application::GetApplication()->GetInterpolationFraction();

		// scale
		Vector2 scale = glm::lerp(LastScale, Scale, alpha);

		// rotation
		double_t rad = glm::radians(Rotation);
		double_t lastrad = glm::radians(LastRotation);

		double_t max = PI * 2.f;
		double_t da = std::fmod(rad - lastrad, max);

		double_t rot = lastrad + (std::fmod(2 * da, max) - da) * alpha;

		// position
		Vector2 pos = glm::lerp(LastPosition, Position, alpha) * scale;

		Mat4 frame = glm::translate(Mat4(1.f), Vector3(pos, 0.f))
			* glm::rotate(Mat4(1.f), rot, Vector3(0.f, 0.f, 1.f))
			* glm::scale(Mat4(1.f), Vector3(scale, 1.f));

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

	Mat4 Object::GetTransform() const
	{
		return glm::translate(Mat4(1.0f), Vector3(Position, 0.f))
			* glm::rotate(Mat4(1.0f), glm::radians(Rotation), Vector3(0.f, 0.f, 1.f))
			* glm::scale(Mat4(1.0f), Vector3(Scale, 1.f));
	}

	Mat4 Object::GetGlobalTransform() const
	{
		Mat4 transform = GetTransform();

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
