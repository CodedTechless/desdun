

#include <corelibraries.hpp>

#include "game.h"

namespace Desdun
{

	void GameLayer::OnAwake()
	{
		Debug::Log("beep!");
	}

	void GameLayer::OnFrameUpdate(const float Delta)
	{

	}

	void GameLayer::OnGameStep(const float Delta)
	{

	}

	Input::Filter GameLayer::OnInputEvent(InputEvent InputObject, bool Processed)
	{

		return Input::Filter::Ignore;
	}

	void GameLayer::OnWindowEvent(WindowEvent WindowObject)
	{

	}
}