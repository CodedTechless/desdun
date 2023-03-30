
#include <object/index.hpp>

#include "runtime.h"

namespace Desdun
{

	Map<Type, BaseRuntimeClass*> Runtime::TypeCollection = {};
	Map<String, BaseRuntimeClass*> Runtime::TypeNameIndexCollection = {};

	void Runtime::start()
	{
		Debug::Log("Registering engine classes...", "Runtime");

		Runtime::registerClass<Instance>("Instance");
		{
			Runtime::registerClass<WorldObject>("WorldObject", Runtime::get<Instance>());
			{
				Runtime::registerClass<Sound>("Sound", Runtime::get<WorldObject>());

				Runtime::registerClass<PhysicsBody>("PhysicsBody", Runtime::get<WorldObject>());
				{
					Runtime::registerClass<DynamicBody>("DynamicBody", Runtime::get<WorldObject>());
					Runtime::registerClass<StaticBody>("StaticBody", Runtime::get<WorldObject>());
				}

				Runtime::registerClass<Camera>("Camera", Runtime::get<WorldObject>());
				Runtime::registerClass<Light>("Light", Runtime::get<WorldObject>());
				Runtime::registerClass<ParticleEmitter>("ParticleEmitter", Runtime::get<WorldObject>());

				Runtime::registerClass<Sprite>("Sprite", Runtime::get<WorldObject>());
				{
					Runtime::registerClass<AnimatedSprite>("AnimatedSprite", Runtime::get<Sprite>());
				}

				Runtime::registerClass<TileMap>("TileMap", Runtime::get<WorldObject>());
			}
		}
	}
}