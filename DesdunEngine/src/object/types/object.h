#pragma once

/*
	base class of all Objects. every game object inherits from this one!
*/

#include <object/instance.h>

#include <glm/glm.hpp>

namespace Desdun
{
	class Object : public Instance
	{
	public:
		RUNTIME_CLASS_DEF(Object);

		// Properties

		Vector2f Position = { 0.0, 0.0 };
		Vector2f Scale = { 1.0, 1.0 };
		float_t Rotation = 0.0;

		float_t ZIndex = 0.0;

		bool Visible = true;
		bool Interpolate = true;

		// Transforms

		Mat4f GetInterpTransform() const;
		Mat4f GetTransform() const;
		Mat4f GetGlobalTransform() const;

	protected:

#if 0
		void Serialise(ByteFile& stream) const;
		void Deserialise(ByteFile& stream);
#endif

		void Serialise(JSONObject& object) const;
		void Deserialise(const JSONObject& object);

	private:

		// Transforms

		Vector2f LastPosition = Position;
		Vector2f LastScale = Scale;
		float_t LastRotation = Rotation;

		friend class Scene;

	};
}