
#include <app/debug/debug.hpp>
#include <resources/resource.hpp>
#include <runtime/runtime.hpp>
#include <graphics/render/renderer.hpp>
#include <objects/index.hpp>

#include <resources/types/fontface.hpp>

#include "app.hpp"

namespace DesdunCore
{
    Application* Application::currentApp = nullptr;
}

namespace DesdunCore
{
	Application::Application()
	{
        currentApp = this;

        Runtime::add<Object>({ "Object" });
        {
            Runtime::add<Entity2D>({ "Entity2D", Runtime::get<Object>() });
            {
                Runtime::add<SoundEmitter2D>({ "SoundEmitter2D", Runtime::get<Entity2D>() });

                Runtime::add<Camera2D>({ "Camera2D", Runtime::get<Entity2D>() });
                Runtime::add<ParticleEmitter2D>({ "ParticleEmitter2D", Runtime::get<Entity2D>() });

                Runtime::add<Sprite>({ "Sprite", Runtime::get<Entity2D>() });
                {
                    Runtime::add<AnimatedSprite>({ "AnimatedSprite", Runtime::get<Sprite>() });
                }

                Runtime::add<TileMap>({ "TileMap", Runtime::get<Entity2D>() });
            }
        }
	}

	Application::~Application()
	{
        stop();
	}

	void Application::init()
	{
        FontFace::init();

        gameWindow = new Window("Desdun", { 1280, 720 });
        
        auto* textureShader = Resource::fetch<Shader>("shaders:tex/tex.tres");
        renderer = new Renderer(textureShader);

        // Start renderer
        imguiLayer = new ImGuiLayer("config:imgui.ini");
        gameLayers.PushOverlay(imguiLayer);
	}

	void Application::stop()
	{
		running = false;
        delete gameWindow;

        gameLayers.clear();
        delete renderer;

        FT_Done_FreeType(*FontFace::library);

        glfwTerminate();
	}

    void Application::start()
    {
        if (running)
        {
            throw Exception("Game loop already active.");
        }

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
                for (Layer* layer : gameLayers) 
                {
                    layer->onGameStep(Accumulator);
                }

                Accumulator -= gameSpeed;
            }

            stepInterpFrac = Accumulator / gameSpeed;

            renderer->clear();
            imguiLayer->begin();

            for (auto* layer : gameLayers)
            {
                layer->onFrameUpdate(FrameTime);
            }

            imguiLayer->end();
            gameWindow->update();
        }
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

    Window* Application::getPrimaryWindow() const 
    {
        return gameWindow;
    };
    
    float Application::getInterpFraction() const 
    { 
        return stepInterpFrac;
    };

    Renderer* Application::getRenderer() const 
    { 
        return renderer;
    };
    
    Application* Application::get()
    {
        return currentApp; 
    };
}


