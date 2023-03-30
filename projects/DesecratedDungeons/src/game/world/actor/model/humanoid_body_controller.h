


#include <game_lib.hpp>

namespace Desdun
{

	class HumanoidBodyController
	{
	public:

		HumanoidBodyController(WorldObject* object)
			: adornee(object) {};

		float animateSpeedModifier = 1.f;
		float animateFactor = 0.f;

		Vector2 lookDirection = { 0.f, 0.f };

		Vector2 eyeOffset = { 3.f, -5.f };

		void update();
		void start();

	private:

		WorldObject* adornee = nullptr;

	};


}