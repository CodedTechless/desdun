


#include <game_lib.hpp>

namespace Desdun
{



	class HumanoidBodyController
	{
	public:

		HumanoidBodyController(WorldObject* object)
			: adornee(object) {};

		enum Pose
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

		Vector2 lookDirection = { 0.f, 0.f };

		Vector2 eyeOffset = { 3.f, -5.f };

		void update();
		void start();

	private:

		HumanoidBodyController::Pose normaliseDirection() const;

		WorldObject* adornee = nullptr;

	};


}