

#include "object.h"

namespace Desdun
{

	Object::~Object()
	{
		for (auto instance : Children)
		{
			delete instance;
		}

		if (Parent)
		{
			Parent->RemoveChild(this);
		}
	}

	void Object::RemoveChild(Object* instance)
	{
		for (auto it = Children.begin(); it != Children.end(); ++it)
		{
			if ((*it)->ID == instance->ID)
			{
				Children.erase(it);
				break;
			}
		}
	}

	Object* Object::FindChild(const std::string& name)
	{
		for (auto instance : Children)
		{
			if (instance->Name == name)
			{
				return instance;
			}
		}

		return nullptr;
	}

	void Object::SetParent(Object* instance)
	{
		if (Parent) Parent->RemoveChild(this);

		Parent = instance;

		Parent->Children.push_back(this);
	};

	/*
		breaks down the transform into its components, then reconstructs it as an interpolation of Last[component] and [component]
	*/
	Mat4 Object::GetInterpTransform() const
	{
		float alpha = Application::GetApplication()->GetInterpolationFraction();

		// scale
		Vector2 scale = glm::lerp(LastScale, Scale, alpha);

		// rotation
		float rad = glm::radians(Rotation);
		float lastrad = glm::radians(LastRotation);

		float max = PI * 2;
		float da = std::fmod(rad - lastrad, max);

		float rot = lastrad + (std::fmod(2 * da, max) - da) * alpha;

		// position
		Vector2 pos = glm::lerp(LastPosition, Position, alpha) * scale;

		Mat4 frame = glm::translate(Mat4(1.f), Vector3(pos, 0.f))
			* glm::rotate(Mat4(1.f), rot, Vector3(0.f, 0.f, 1.f))
			* glm::scale(Mat4(1.f), Vector3(scale, 1.f));

		if (Parent != nullptr)
		{
			frame = Parent->GetInterpTransform() * frame;
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

		if (Parent != nullptr)
		{
			transform = Parent->GetGlobalTransform() * transform;
		}

		return transform;
	}

}
