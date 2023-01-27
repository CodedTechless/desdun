#pragma once

#include <resource/types/animation_sequence.h>
#include <object/types/object.h>

namespace Desdun
{

	class AnimatedSprite : public Object
	{
	public:
		RUNTIME_CLASS_DEF(AnimatedSprite);





	private:
		std::unordered_map<std::string, AnimationSequence*> animationSequences = {};

		float timePosition = 0.f;
	};

}