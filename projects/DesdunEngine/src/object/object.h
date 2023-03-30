#pragma once

/*
	base class of all Objects. every game object inherits from this one!
*/

#include <object/instance.h>

#include <glm/glm.hpp>

namespace Desdun
{
	class WorldObject : public Instance
	{
	public:
		serialisable(WorldObject)

		// Properties

		Vector2f position = { 0.0, 0.0 };
		Vector2f scale = { 1.0, 1.0 };
		float_t rotation = 0.0;

		float_t zIndex = 0.0;

		bool visible = true;
		bool interpolate = false;

		// Transforms

		Mat4f getInterpTransform() const;
		Mat4f getTransform() const;
		Mat4f getGlobalTransform() const;

		Vector2f getInterpPosition() const;
		Vector2f getInterpScale() const;
		float getInterpRotation() const;

	protected:

#if 0
		void Serialise(ByteFile& stream) const;
		void Deserialise(ByteFile& stream);
#endif

		void serialise(JSONObject& object) const;
		void deserialise(const JSONObject& object);

	private:

		// Transforms

		Vector2f LastPosition = position;
		Vector2f LastScale = scale;
		float_t LastRotation = rotation;

		friend class Scene;

	};
}