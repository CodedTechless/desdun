

#include "animation_sequence.h"

namespace Desdun
{

	void AnimationSequence::load(const std::string& path)
	{
		std::ifstream stream(path);
		json jsonObject;

		stream >> jsonObject;

		jsonObject.at("frameRate").get_to(frameRate);
		jsonObject.at("frames").get_to(frames);

		for (Frame& frame : frames)
		{
			length += frame.length;
		};
	}

}