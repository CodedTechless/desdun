#pragma once

/*
	base class of all Objects. every game object inherits from this one!
*/

#include <desdun_engine/src/instance/instance.hpp>

#include <desdun_engine/include/glm/glm.hpp>

namespace Desdun
{
	class WorldObject : public Instance
	{
	public:
		serialisable(WorldObject)

		// Properties

		float_t zIndex = 0.0;

		bool visible = true;
		bool interpolate = false;

		void setPosition(const Vector2f& newPos);
		void setScale(const Vector2f& newScale);
		void setRotation(float_t newRot);

		void translate(const Vector2f& pos);
		void resize(const Vector2f& size);
		void rotate(float_t rot);

		Vector2f getPosition() const;
		Vector2f getScale() const;
		float_t getRotation() const;

		Vector2f getGlobalPosition();
		Vector2f getGlobalScale();
		float_t getGlobalRotation();

		Mat4f getGlobalTransform();

	protected:

		Mat4f getRenderTransform();

		Vector2f getLocalInterpPosition();
		Vector2f getLocalInterpScale();
		float_t getLocalInterpRotation();

		void serialise(JSONObject& object) const;
		void deserialise(const JSONObject& object);

	private:

		Vector2f position = { 0.0, 0.0 };
		Vector2f scale = { 1.0, 1.0 };
		float_t rotation = 0.0;

		Vector2f positionLast = position; // local space
		Vector2f scaleLast = scale; // local space
		float_t rotationLast = rotation; // local space

		Vector2f positionInterp = position;
		Vector2f scaleInterp = scale;
		float_t rotationInterp = rotation;

		Vector2f positionGlobal = position;
		Vector2f scaleGlobal = scale;
		float_t rotationGlobal = rotation;
		
		// Transforms

		FLAG dirtyGlobal = true;
		FLAG dirtyInterp = true;

		FLAG interpolateThisStep = false;

		// this transform is the actual rendered position of the object in the world,
		// while the other values (xGlobal) represent the global position as of the last step
		Mat4f transformRender { 1.f };
		Mat4f transformGlobal { 1.f };

		// runs a dirty check. if any of the position, scale or rotation values have changed since
		// the last step, dirtyGlobal will be set to true and so will interpolateThisStep
		void checkDirty();
 
		// this marks the *global* pos, scale and rot dirty, meaning that if they are fetched again
		// then they should be recalculated.
		void markDirty() override;
		void markInterpDirty();

		// ages up the transform (copies the current transform info into transformGlobalLast)
		void ageLocalTransform();

		// bakes the transform, which updates global pos, scale and rot and then bakes it into transformGlobal
		void bakeGlobalTransform();
		void bakeInterpolatedTransform();

		friend class Scene;

	};
}