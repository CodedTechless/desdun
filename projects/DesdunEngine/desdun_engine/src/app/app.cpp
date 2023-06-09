
#include <desdun_engine/src/app/debug/debug.h>
#include <desdun_engine/src/app/resource/resource.hpp>
#include <desdun_engine/src/app/runtime/runtime.h>
#include <desdun_engine/src/graphics/render/renderer.h>
#include <desdun_engine/src/instance/index.hpp>

#include "app.h"

namespace Desdun
{
    Application* Application::currentApp = nullptr;
}

namespace Desdun
{
	Application::Application()
	{
        currentApp = this;
	}

	Application::~Application()
	{
        delete gameWindow;

        gameLayers.clear();
        Renderer::stop();
	}

    void Application::start()
    {
        Debug::Log("Registering engine classes...", "Runtime");

        Runtime::add<Instance>({ "Instance" });
        {
            Runtime::add<WorldObject>({ "WorldObject", Runtime::get<Instance>() });
            {
                Runtime::add<Sound>({ "Sound", Runtime::get<WorldObject>() });

                Runtime::add<Camera>({ "Camera", Runtime::get<WorldObject>() });
                Runtime::add<Light>({ "Light", Runtime::get<WorldObject>() });
                Runtime::add<ParticleEmitter>({ "ParticleEmitter", Runtime::get<WorldObject>() });

                Runtime::add<Sprite>({ "Sprite", Runtime::get<WorldObject>() });
                {
                    Runtime::add<AnimatedSprite>({ "AnimatedSprite", Runtime::get<Sprite>() });
                }

                Runtime::add<TileMap>({ "TileMap", Runtime::get<WorldObject>() });
            }
        }
    }

	void Application::run()
	{
		if (running)
		{
            return;
		}

        gameWindow = new Window("Desecrated Dungeons", { 1280, 720 });
        Renderer::start();

        imguiLayer = new ImGuiLayer("config/imgui.ini");
        gameLayers.PushOverlay(imguiLayer);

		running = true;
        float Time = 0.f;
        float CurrentTime = (float)glfwGetTime();
        float Accumulator = 0.f;

        size_t Frames = 0, Updates = 0;

        while (running)
        {
            float NewTime = (float)glfwGetTime();
            float FrameTime = std::min(NewTime - CurrentTime, 0.25f);
            CurrentTime = NewTime;

            Time += FrameTime;
            Accumulator += FrameTime;

            while (Accumulator >= gameSpeed)
            {
                for (Layer* a_Layer : gameLayers) {
                    a_Layer->onGameStep(Accumulator);
                }

                Accumulator -= gameSpeed;
            }

            stepInterpFrac = Accumulator / gameSpeed;
            
            gameWindow->clear();
            imguiLayer->begin();

            for (auto* Layer : gameLayers)
            {
                Layer->onFrameUpdate(FrameTime);
            }

            imguiLayer->end();
            gameWindow->update();
		}
	}

	void Application::end()
	{
		running = false;
	}

    void Application::pushInputEvent(Input::Event& event)
    {
        for (auto i = gameLayers.rbegin(); i != gameLayers.rend(); ++i)
        {
            (*i)->onInputEvent(event);

            if (event.absorbed)
                break;
        }
    }

    void Application::pushWindowEvent(const Window::Event& windowEvent)
    {
        for (auto* Layer : gameLayers)
        {
            Layer->onWindowEvent(windowEvent);
        }
    }
}


