

#include <desdun_engine/desdun_engine.hpp>

namespace Desdun
{

	class HumanoidBodyController
	{
	public:

		HumanoidBodyController(WorldObject* object)
			: adornee(object) {};

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

		void update();
		void start();

	private:

		Pose lookNormal = Pose::LEFT;
		Vector2 lookDirection = { 0.f, 0.f };
		WorldObject* adornee = nullptr;

		void updatePose();
		void updateLookNormal();
	};


}