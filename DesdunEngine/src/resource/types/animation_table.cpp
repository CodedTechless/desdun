

#include "animation_table.hpp"


namespace Desdun
{

	void AnimationTable::load(const String& path)
	{
		std::ifstream stream(path);
		json jsonObject;

		stream >> jsonObject;

		for (auto& [k, v] : jsonObject.items())
		{
			animations.emplace(k, CreateRef<AnimationSequence>(v.get<AnimationSequence>()));
		}
	}

}