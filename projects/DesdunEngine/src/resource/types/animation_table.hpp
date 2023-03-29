#pragma once

#include <resource/resource.hpp>
#include "image.h"

namespace Desdun
{

	struct Frame
	{
		Image* image;
		uint duration = 0;

		friend void from_json(const json& jsonObject, Frame& frame)
		{
			std::string imagePath = jsonObject.at("imagePath");
			if (imagePath != "")
			{
				frame.image = Resource::fetch<Image>(imagePath);
			}

			jsonObject.at("duration").get_to(frame.duration);
		};

		friend void to_json(json& jsonObject, const Frame& frame)
		{
			if (frame.image)
				jsonObject["imagePath"] = frame.image->getPath();
			else
				jsonObject["imagePath"] = "";

			jsonObject["duration"] = frame.duration;
		};

	};

	class AnimationSequence
	{
	public:

		bool isLooped = true;
		List<Frame> frames = {};	// list of all included frames

		float getDuration() const { return duration; };

		friend void from_json(const json& object, AnimationSequence& sequence)
		{
			object.get_to(sequence.frames);

			for (Frame& frame : sequence.frames)
			{
				sequence.duration += frame.duration;
			};
		}

		friend void to_json(json& object, const AnimationSequence& sequence)
		{
			object = sequence.frames;
		}

	private:

		float duration = 0.f;
	};

	class AnimationTable : public Resource
	{
	public:
		Map<String, Ref<AnimationSequence>> animations = {};

		void load(const String& path);
	};
}