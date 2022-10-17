

#include <game/instances/Actor.hpp>

#include <gamelib.hpp>
#include <uuid.hpp>

#include "game.h"

namespace Desdun
{

	template<typename T>
	T* Game::Create()
	{
		std::string NewID = UUID::Generate();

		T* NewInst = new T(this, NewID);
		Instances.push_back((Instance*)NewInst);
		InstanceCount++;

		NewInst->OnAwake();

		return NewInst;
	}

	void Game::OnAwake()
	{
		Debug::Log("beep!");

		Instances.reserve(MAX_INSTANCES);

		auto* inst = Create<Actor>();
		inst->Name = "Actor";

	}

	void Game::OnFrameUpdate(const float Delta)
	{
		RenderCamera cam = {};
		cam.SetOrthoSize(Vector2(800, 600));

		RenderInterface::BeginScene(cam);

		for (auto i = Instances.begin(); i < Instances.begin() + InstanceCount; ++i)
		{
			(*i)->OnFrameUpdate(Delta);
		}

		RenderInterface::EndScene();
	}

	void Game::OnGameStep(const float Delta)
	{
		for (auto i = Instances.begin(); i < Instances.begin() + InstanceCount; ++i)
		{
			(*i)->OnGameStep(Delta);
		}
	}

	Input::Filter Game::OnInputEvent(InputEvent InputObject, bool Processed)
	{
		for (auto i = Instances.begin(); i < Instances.begin() + InstanceCount; ++i)
		{
			(*i)->OnInputEvent(InputObject, Processed);
		}

		return Input::Filter::Ignore;
	}

	void Game::OnWindowEvent(WindowEvent WindowObject)
	{
		for (auto i = Instances.begin(); i < Instances.begin() + InstanceCount; ++i)
		{
			(*i)->OnWindowEvent(WindowObject);
		}
	}
}