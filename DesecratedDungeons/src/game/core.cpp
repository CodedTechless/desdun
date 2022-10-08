
#include <GL/glew.h>
#include <glfw3.h>

#include <core/window.h>
#include <core/debug/debug.h>

#include "layers/game.h"
#include "core.h"

namespace Desdun
{
	Game* Game::GameInstance = nullptr;

	Game::Game()
	{
		GameInstance = this;
		
		GameWindow = new Window("Desecrated Dungeons", { 800, 600 });

        Layer* MainLayer = new GameLayer("GameLayer");
        GameLayers.PushLayer(MainLayer);

        /*
        ImGuiLayer = new ImGuiLayer(ImGuiIniFileName);
        Layers.PushOverlay(a_ImGuiLayer);
        */
	}

	Game::~Game()
	{

	}

	void Game::Start()
	{
		if (Running)
		{
            return;
		}

		Running = true;

		while (Running)
		{
            GameWindow->Clear();

            GameWindow->Update();
		}
	}

	void Game::End()
	{
		Running = false;
	}

    void Game::PushInputEvent(const InputEvent& inputEvent)
    {
        //Debug::Log("Event " + std::to_string((int)inputEvent.InputType) + " " + std::to_string((int)inputEvent.InputState) + " " + std::to_string((int)inputEvent.KeyCode) + " " + std::to_string((int)inputEvent.MouseCode) + " (" + std::to_string(inputEvent.Delta.x) + ", " + std::to_string(inputEvent.Delta.y) + ") (" + std::to_string(inputEvent.Position.x) + ", " + std::to_string(inputEvent.Position.y) + ")", "Application");

        /*
        if (a_ImGuiLayer->GetAbsorbInputs())
        {
            ImGuiIO& io = ImGui::GetIO();
            if (((inputEvent.InputType == Input::Type::Mouse || inputEvent.InputType == Input::Type::Scrolling) && io.WantCaptureMouse) ||
                (inputEvent.InputType == Input::Type::Keyboard && io.WantCaptureKeyboard))
            {
                return;
            }
        }
        */

        bool Processed = false;

        for (auto i = GameLayers.rbegin(); i != GameLayers.rend(); ++i)
        {
            Input::Filter Response = (*i)->OnInputEvent(inputEvent, Processed);

            if (Response == Input::Filter::Stop)
                break;
            else if (Response == Input::Filter::Continue)
                Processed = true;
        }
    }

    void Game::PushWindowEvent(const WindowEvent& windowEvent)
    {
        for (auto* Layer : GameLayers)
        {
            Layer->OnWindowEvent(windowEvent);
        }
    }
}


