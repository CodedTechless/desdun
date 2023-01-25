#pragma once


#include <object/types/object.h>

namespace Desdun
{

	struct Frame
	{
		Image* image;

	};

	struct AnimationSequence
	{
		float frameRate = 30.f;


		std::vector<Frame> frames = {};
	};

	class AnimatedSprite : public Object
	{
	public:
		RUNTIME_CLASS_DEF(AnimatedSprite);



		std::unordered_map<std::string, AnimationSequence> animationSequences = {};
	};

}