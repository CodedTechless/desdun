#pragma once

#include <desdun_engine/src/app/resource/descendants/animation_table.hpp>

#include "sprite.hpp"

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

		void setAnimationTable(AnimationTable* anim);
		AnimationTable* getAnimationTable() const;		

		// plays the specified animation from the set AnimationTable.
		void play(const String& name, bool seek = false);
		void play();
		void pause();

		uint getFrame() const;
		bool isPlaying() const;
		
		void onFrameUpdate(float delta) override;

	protected:

		void serialise(JSONObject& object) const override;
		void deserialise(const JSONObject& object) override;

	private:

		AnimationTable* animTable = nullptr;

		String currentPlaying = "";
		Ref<AnimationSequence> currentSequence = nullptr;

		bool playing = false;

		uint frame = 0;
		float elapsed = 0.f;
	};

}