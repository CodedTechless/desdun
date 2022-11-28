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

		Vector2 Position = { 0.0, 0.0 };
		Vector2 Scale = { 1.0, 1.0 };
		double_t Rotation = 0.0;

		double_t ZIndex = 0.0;

		bool Visible = true;
		bool Interpolate = true;

		// Transforms

		Mat4 GetInterpTransform() const;
		Mat4 GetTransform() const;
		Mat4 GetGlobalTransform() const;

	protected:

#if 0
		void Serialise(ByteFile& stream) const;
		void Deserialise(ByteFile& stream);
#endif

		void Serialise(JSONObject& object) const;
		void Deserialise(const JSONObject& object);

	private:

		// Transforms

		Vector2 LastPosition = Position;
		Vector2 LastScale = Scale;
		double_t LastRotation = Rotation;

		friend class Scene;

	};
}