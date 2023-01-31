

#include "animation_sequence.h"

namespace Desdun
{

	void AnimationSequence::load(const std::string& path)
	{
		std::ifstream stream(path);
		json jsonObject;

		stream >> jsonObject;

		jsonObject.get_to(frames);

		for (Frame& frame : frames)
		{
			duration += frame.duration;
		};
	}

}