
#include "animated_sprite.hpp"


namespace Desdun
{

	void AnimatedSprite::setAnimationTable(AnimationTable* anim)
	{
		animTable = anim;
	}

	void AnimatedSprite::play()
	{
		if (currentSequence == nullptr)
			return;

		playing = true;
	}

	void AnimatedSprite::play(const String& name, bool seek)
	{
		if (currentPlaying == name)
		{
			return;
		}

		if (animTable->animations.find(name) == animTable->animations.end())
			throw InvalidAnimationException(name, animTable->getPath());

		if (seek == false)
		{
			frame = 0;
			elapsed = 0.f;
		}

		playing = true;

		currentSequence = animTable->animations[name];
		currentPlaying = name;
	}

	void AnimatedSprite::pause()
	{
		playing = false;
	}

	void AnimatedSprite::onFrameUpdate(float delta)
	{
		if (currentSequence != nullptr)
		{
			Frame currentFrame = currentSequence->frames[frame];

			if (playing == true)
			{
				elapsed += delta * playbackSpeed;

				float duration = currentFrame.duration / 1000.f;
				if (elapsed > duration)
				{
					elapsed -= duration;

					if (frame >= currentSequence->frames.size() - 1)
					{
						frame = 0;

						if (currentSequence->isLooped == false)
						{
							playing = false;
						}
					}
					else
					{
						frame++;
					}

					currentFrame = currentSequence->frames[frame];
				}
			}

			image = currentFrame.image;
		};

		Sprite::onFrameUpdate(delta);
	}

	void AnimatedSprite::serialise(JSONObject& object) const
	{
		if (animTable)
			object["animTable"] = animTable->getPath();

		object["currentPlaying"] = currentPlaying;
		object["playbackSpeed"] = playbackSpeed;
		object["playing"] = playing;

		Sprite::serialise(object);
	}

	void AnimatedSprite::deserialise(const JSONObject& object)
	{
		String path = object.at("animTable").get<String>();
		if (path != "")
		{
			setAnimationTable(Resource::fetch<AnimationTable>(path));
		}

		if (object.at("playing").get<bool>() == true)
		{
			play(object.at("currentPlaying").get<String>());
		}
		object.at("playbackSpeed").get_to(playbackSpeed);

		Sprite::deserialise(object);
	}

	uint AnimatedSprite::getFrame() const 
	{ 
		return frame; 
	};

	bool AnimatedSprite::isPlaying() const 
	{ 
		return playing;
	};

	AnimationTable* AnimatedSprite::getAnimationTable() const 
	{ 
		return animTable;
	};

}