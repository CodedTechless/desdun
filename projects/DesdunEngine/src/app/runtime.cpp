
#include <object/index.hpp>

#include "runtime.h"

namespace Desdun
{

	std::unordered_map<std::type_index, BaseRuntimeClass*> Runtime::TypeCollection = {};
	std::unordered_map<std::string, BaseRuntimeClass*> Runtime::TypeNameIndexCollection = {};

	void Runtime::start()
	{
		Debug::Log("Registering engine classes...", "Runtime");

		Runtime::registerClass<Instance>("Instance");
		{
			Runtime::registerClass<WorldObject>("WorldObject", Runtime::Get<Instance>());
			{
				Runtime::registerClass<Sound>("Sound", Runtime::Get<WorldObject>());

				Runtime::registerClass<PhysicsBody>("PhysicsBody", Runtime::Get<WorldObject>());
				{
					Runtime::registerClass<DynamicBody>("DynamicBody", Runtime::Get<WorldObject>());
					Runtime::registerClass<StaticBody>("StaticBody", Runtime::Get<WorldObject>());
				}

				Runtime::registerClass<Camera>("Camera", Runtime::Get<WorldObject>());
				Runtime::registerClass<Light>("Light", Runtime::Get<WorldObject>());
				Runtime::registerClass<ParticleEmitter>("ParticleEmitter", Runtime::Get<WorldObject>());

				Runtime::registerClass<Sprite>("Sprite", Runtime::Get<WorldObject>());
				{
					Runtime::registerClass<AnimatedSprite>("AnimatedSprite", Runtime::Get<Sprite>());
				}

				Runtime::registerClass<TileMap>("TileMap", Runtime::Get<WorldObject>());
			}
		}
	}
}