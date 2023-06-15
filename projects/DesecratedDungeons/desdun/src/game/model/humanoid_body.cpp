

#include "humanoid_body.hpp"

namespace Desdun
{

	HumanoidBodyController::HumanoidBodyController(WorldObject* object)
		: adornee(object) 
	{
	}

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

		updatePose();

		auto* legs = (AnimatedSprite*)adornee->findChild("legs");
		legs->playbackSpeed = 1.f * animateSpeedModifier;

		if (animateFactor > 0.1f)
			legs->play("legs_walk");
		else
			legs->play("legs_idle");
	}

	void HumanoidBodyController::updateLookNormal()
	{
		Vector2 dir = glm::round(lookDirection);

		if (dir.x == -1.f)
		{
			if (dir.y == -1.f)
			{
				lookNormal = Pose::UPLEFT;
			}
			else if (dir.y == 0.f)
			{
				lookNormal = Pose::LEFT;
			}
			else if (dir.y == 1.f)
			{
				lookNormal = Pose::DOWNLEFT;
			}
		}
		else if (dir.x == 0.f)
		{
			if (dir.y == -1.f)
			{
				lookNormal = Pose::UP;
			}
			else if (dir.y == 1.f)
			{
				lookNormal = Pose::DOWN;
			}
		}
		else if (dir.x == 1.f)
		{
			if (dir.y == -1.f)
			{
				lookNormal = Pose::LEFT;
			}
			else if (dir.y == 0.f)
			{
				lookNormal = Pose::RIGHT;
			}
			else if (dir.y == 1.f)
			{
				lookNormal = Pose::DOWNRIGHT;
			}
		}
	}

	void HumanoidBodyController::updatePose()
	{
		switch (lookNormal)
		{
			case Pose::LEFT:
			{

				break;
			}
			case Pose::DOWNLEFT:
			{
				break;
			}
			case Pose::DOWN:
			{
				break;
			}
			case Pose::DOWNRIGHT:
			{
				break;
			}
			case Pose::RIGHT:
			{
				break;
			}
			case Pose::UPRIGHT:
			{
				break;
			}
			case Pose::UP:
			{
				break;
			}
			case Pose::UPLEFT:
			{
				break;
			}
		}
	}

	void HumanoidBodyController::setLookDirection(const Vector2 direction)
	{
		lookDirection = direction;
		updateLookNormal();
	}

}