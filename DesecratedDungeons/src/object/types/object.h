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

		Vector2 Position = { 0.f, 0.f };
		Vector2 Scale = { 1.f, 1.f };
		float Rotation = 0.f;

		float ZIndex = 0.f;

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

	private:

		// Transforms

		Vector2 LastPosition = Position;
		Vector2 LastScale = Scale;
		float LastRotation = Rotation;

		friend class Scene;

	};
}