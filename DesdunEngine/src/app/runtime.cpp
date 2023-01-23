
#include <object/index.hpp>

#include "runtime.h"

namespace Desdun
{

	std::unordered_map<std::type_index, BaseRuntimeClass*> Runtime::TypeCollection = {};
	std::unordered_map<std::string, BaseRuntimeClass*> Runtime::TypeNameIndexCollection = {};

	void Runtime::Start()
	{
		Runtime::Add<Instance>("Instance");
		{
			Runtime::Add<Object>("Object", Runtime::Get<Instance>());
			{
				Runtime::Add<Sound>("Sound", Runtime::Get<Object>());

				Runtime::Add<DynamicBody>("DynamicBody", Runtime::Get<Object>());
				Runtime::Add<KinematicBody>("KinematicBody", Runtime::Get<Object>());
				Runtime::Add<StaticBody>("StaticBody", Runtime::Get<Object>());

				Runtime::Add<Camera>("Camera", Runtime::Get<Object>());
				Runtime::Add<Light>("Light", Runtime::Get<Object>());
				Runtime::Add<ParticleEmitter>("ParticleEmitter", Runtime::Get<Object>());

				Runtime::Add<Sprite>("Sprite", Runtime::Get<Object>());
				Runtime::Add<AnimatedSprite>("AnimatedSprite", Runtime::Get<Object>());
				Runtime::Add<TileMap>("TileMap", Runtime::Get<Object>());
			}
		}
	}
}