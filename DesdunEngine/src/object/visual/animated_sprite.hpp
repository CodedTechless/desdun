#pragma once

#include <resource/types/animation_table.hpp>
#include <object/visual/sprite.hpp>

namespace Desdun
{

	class InvalidAnimationException : public virtual Exception 
	{
	public:
		InvalidAnimationException(const std::string& tN, const std::string& aPN)
			: Exception(std::format("Animation {} was invalid or didn't exist in selected AnimationTable {}.", tN, aPN)) {};
	};

	class AnimatedSprite : public Sprite
	{
	public:
		serialisable(AnimatedSprite)
		
		float playbackSpeed = 1.f;

		void setAnimationTable(AnimationTable* anim)
		{
			animTable = anim;
		}

		// plays the specified animation from the set AnimationTable.
		void play(const std::string& name, bool seek = false)
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

			isPlaying = true;
			
			currentSequence = animTable->animations[name];
			currentPlaying = name;
		}

		// resumes the current animation
		void play()
		{
			if (currentSequence == nullptr)
				return;

			isPlaying = true;
		}

		void pause()
		{
			isPlaying = false;
		}

		void onFrameUpdate(float delta) override
		{
			if (currentSequence != nullptr)
			{
				Frame currentFrame = currentSequence->frames[frame];

				if (isPlaying == true)
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
								isPlaying = false;
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

	private:
		AnimationTable* animTable = nullptr;

		std::string currentPlaying = "";
		Ref<AnimationSequence> currentSequence = nullptr;

		bool isPlaying = false;

		uint frame = 0;
		float elapsed = 0.f;
	};

}