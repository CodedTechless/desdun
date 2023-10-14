

#include "animation_table.hpp"


namespace DesdunCore
{

	void AnimationTable::unload()
	{
		animations.clear();
	}

	void AnimationTable::load()
	{
		std::ifstream stream(getPath());
		json jsonObject;

		stream >> jsonObject;

		for (auto& [k, v] : jsonObject.items())
		{
			animations.emplace(k, CreateRef<AnimationSequence>(v.get<AnimationSequence>()));
		}
	}

}