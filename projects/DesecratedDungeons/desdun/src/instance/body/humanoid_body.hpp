#pragma once

#include <desdun_engine/desdun_engine.hpp>

namespace Desdun
{

	class HumanoidBodyController : public WorldObject
	{
	public:
	serialisable(HumanoidBodyController)

		enum class Pose
		{
			LEFT = 0,
			DOWNLEFT = 1,
			DOWN = 2,
			DOWNRIGHT = 3,
			RIGHT = 4,
			UPRIGHT = 5,
			UP = 6,
			UPLEFT = 7
		};

		float animateSpeedModifier = 1.f;
		float animateFactor = 0.f;

		Vector2 eyeOffset = { 3.f, -5.f };

		void setLookDirection(const Vector2 direction);

		void updateBody();
		void setupBody();

	protected:
		
		void serialise(JSONObject& object) const override;
		void deserialise(const JSONObject& object) override;
		
	private:

		Pose lookNormal = Pose::LEFT;
		Vector2 lookDirection = { 0.f, 0.f };

		void updatePose();
		void updateLookNormal();
	};


}