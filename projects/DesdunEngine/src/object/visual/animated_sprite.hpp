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

			playing = true;
			
			currentSequence = animTable->animations[name];
			currentPlaying = name;
		}

		// resumes the current animation
		void play()
		{
			if (currentSequence == nullptr)
				return;

			playing = true;
		}

		void pause()
		{
			playing = false;
		}

		void onFrameUpdate(float delta) override
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
		};

		uint getFrame() const { return frame; };
		bool isPlaying() const { return playing; };
		AnimationTable* getAnimationTable() const { return animTable; };

	private:
		AnimationTable* animTable = nullptr;

		std::string currentPlaying = "";
		Ref<AnimationSequence> currentSequence = nullptr;

		bool playing = false;

		uint frame = 0;
		float elapsed = 0.f;
	};

}