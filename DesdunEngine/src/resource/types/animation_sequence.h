#pragma once

#include <resource/types/image.h>
#include <resource/resource.hpp>

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

	class AnimationSequence : public Resource
	{
	public:

		bool isLooped = true;

		std::vector<Frame> frames = {};	// list of all included frames
		
		void load(const std::string& path) override;
		float getDuration() const { return duration; };

	private:

		float duration = 0.f;
	};
}

