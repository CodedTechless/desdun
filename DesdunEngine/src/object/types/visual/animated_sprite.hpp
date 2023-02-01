#pragma once

#include <resource/types/animation_sequence.h>
#include <object/types/visual/sprite.hpp>

namespace Desdun
{

	struct AnimationSequenceEmplaceOptions
	{
		std::string name;
		AnimationSequence* sequence;
	};

	class AnimatedSprite : public Sprite
	{
	public:
		RUNTIME_CLASS_DEF(AnimatedSprite);

		float playbackSpeed = 1.f;

		// sets the sequence "name" to AnimationSequence
		void setSequence(const std::string& name, AnimationSequence* sequence)
		{
			if (animationSequences.find(name) != animationSequences.end())
			{
				throw new Exception("Animation already exists.");
			};

			animationSequences[name] = sequence;
		}

		void setSequences(std::initializer_list<AnimationSequenceEmplaceOptions> sequences)
		{
			for (auto& sequenceHint : sequences)
			{
				animationSequences[sequenceHint.name] = sequenceHint.sequence;
			}
		}

		// plays the specified animation from animationSequences
		void play(const std::string& name, bool seek = false)
		{
			if (currentPlaying == name)
			{
				return;
			}
			
			if (animationSequences.find(name) == animationSequences.end())
			{
				throw new Exception("Animation does not exist.");
			}
			
			if (seek == false)
			{
				frame = 0;
				elapsed = 0.f;
			}

			isPlaying = true;
			
			currentSequence = animationSequences[name];
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
		std::unordered_map<std::string, AnimationSequence*> animationSequences = {};

		std::string currentPlaying = "";
		AnimationSequence* currentSequence = nullptr;

		bool isPlaying = false;

		uint frame = 0;
		float elapsed = 0.f;
	};

}