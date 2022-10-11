

#include <gamelib.hpp>

#include <uuid.hpp>

#include "game.h"

namespace Desdun
{

	template<typename T>
	ptr<T> Game::Create()
	{
		std::string NewID = UUID::Generate();

		ptr<T> NewInst = CreatePointer<T>(this, NewID);
		Instances[InstanceCount++] = NewInst;

		NewInst->OnAwake();

		return NewInst;
	}

	void Game::OnAwake()
	{
		Debug::Log("beep!");

		ptr<Instance> inst = Create<Instance>();
		inst->Name = "NewInstance";

		ptr<Image> image = CreatePointer<Image>("assets/goofy.png");

		GoofyAhh = CreatePointer<TextureArray>(Vector2(300.f,  300.f), 16);
		GoofyAhh->SetLayer(0, image);
	}

	void Game::OnFrameUpdate(const float Delta)
	{
		for (auto i = Instances.begin(); i < Instances.begin() + InstanceCount; ++i)
		{
			(*i)->OnFrameUpdate(Delta);
		}

		Mat4 Transform = glm::translate(Mat4(1.f), Vector3(100.f, 100.f, 0.f))
//			* glm::rotate(Mat4(1.f), glm::radians(0.f), Vector3(0.f, 0.f, 1.f))
			* glm::scale(Mat4(1.f), Vector3(100.f, 100.f, 1.f));
		
		RenderCamera cam = {};
		cam.SetOrthoSize(Vector2(800, 600));

		RenderInterface::BeginScene(cam);

		RenderInterface::Submit({
			Transform, Color4(1.f, 1.f, 1.f, 1.f),
			{
				{ 0.f, 0.f },
				{ 1.f, 0.f },
				{ 1.f, 1.f },
				{ 0.f, 1.f }
			},

			0,
			GoofyAhh,
			nullptr,

			0
		});

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