#pragma once

#include <resource/types/image.h>
#include <resource/resource.hpp>

namespace Desdun
{

	struct Frame
	{
		Image* image;
		uint length = 0;

		friend void from_json(const json& jsonObject, Frame& frame)
		{
			std::string imagePath = jsonObject.at("imagePath");
			if (imagePath != "")
			{
				frame.image = Resource::fetch<Image>(imagePath);
			}

			jsonObject.at("length").get_to(frame.length);
		};

		friend void to_json(json& jsonObject, const Frame& frame)
		{
			if (frame.image)
				jsonObject["imagePath"] = frame.image->getPath();
			else
				jsonObject["imagePath"] = "";

			jsonObject["length"] = frame.length;
		};

	};

	class AnimationSequence : public Resource
	{
	public:

		uint length = 0; // the total length in frames
		float frameRate = 30.f; // the frame rate, in fps
		
		std::vector<Frame> frames = {};	// list of all included frames

		void load(const std::string& path) override;

	};
}

