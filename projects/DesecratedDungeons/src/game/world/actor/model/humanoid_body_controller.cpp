

#include "humanoid_body_controller.h"

namespace Desdun
{

	void HumanoidBodyController::start()
	{
		auto* body = (AnimatedSprite*)adornee->findChild("torso");
		body->play("torso_idle");

		auto* legs = (AnimatedSprite*)adornee->findChild("legs");
		legs->play("legs_idle");

		auto* leftEye = (AnimatedSprite*)body->findChild("leftEye");
		auto* rightEye = (AnimatedSprite*)body->findChild("rightEye");

		rightEye->play("eye_idle");
		leftEye->play("eye_idle");

		auto* shoulders = (WorldObject*)body->findChild("shoulders");

		auto* leftHand = (Sprite*)shoulders->findChild("leftHand");
		auto* rightHand = (Sprite*)shoulders->findChild("rightHand");

		leftHand->visible = false;
		rightHand->visible = false;

		update();
	}

	void HumanoidBodyController::update()
	{
		auto* body = (AnimatedSprite*)adornee->findChild("torso");

		auto* leftEye = (AnimatedSprite*)body->findChild("leftEye");
		auto* rightEye = (AnimatedSprite*)body->findChild("rightEye");

		Vector2 eyeOffsetModifier = Vector2(0.f, (float)body->getFrame());

		leftEye->setPosition(eyeOffset + eyeOffsetModifier);
		rightEye->setPosition(eyeOffset * Vector2(-1.f, 1.f) + eyeOffsetModifier);

		auto* legs = (AnimatedSprite*)adornee->findChild("legs");
		legs->playbackSpeed = 1.f * animateSpeedModifier;

		if (animateFactor > 0.1f)
			legs->play("legs_walk");
		else
			legs->play("legs_idle");
	}

}