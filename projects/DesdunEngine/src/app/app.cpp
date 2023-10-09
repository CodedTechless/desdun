
#include <src/app/debug/debug.h>
#include <src/resources/resource.hpp>
#include <src/runtime/runtime.h>
#include <src/graphics/render/renderer.h>
#include <src/instances/index.hpp>

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

        Debug::Log("Registering engine classes...", "Runtime");

        Runtime::add<Instance>({ "Instance" });
        {
            Runtime::add<WorldObject>({ "WorldObject", Runtime::get<Instance>() });
            {
                Runtime::add<Sound>({ "Sound", Runtime::get<WorldObject>() });

                Runtime::add<Camera>({ "Camera", Runtime::get<WorldObject>() });
                Runtime::add<ParticleEmitter>({ "ParticleEmitter", Runtime::get<WorldObject>() });

                Runtime::add<Sprite>({ "Sprite", Runtime::get<WorldObject>() });
                {
                    Runtime::add<AnimatedSprite>({ "AnimatedSprite", Runtime::get<Sprite>() });
                }

                Runtime::add<TileMap>({ "TileMap", Runtime::get<WorldObject>() });
            }
        }
	}

	Application::~Application()
	{
        delete gameWindow;

        stop();
        gameLayers.clear();

        delete renderer;

        glfwTerminate();
	}

	void Application::init()
	{
        Debug::Log("initialising...", "Application");

        gameWindow = new Window("Desecrated Dungeons", { 1280, 720 });

        // Start renderer


        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageCallback(Debug::OpenGLMessage, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

        glEnable(GL_BLEND);
        glDisable(GL_DEPTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        char* Version = (char*)glGetString(GL_VERSION);
        Debug::Log("using OpenGL " + std::string(Version), "Application");

        auto* textureShader = Resource::fetch<Shader>("shaders:tex/tex.shader.json");
        renderer = new Renderer(textureShader);

        imguiLayer = new ImGuiLayer("config:imgui.ini");
        gameLayers.PushOverlay(imguiLayer);
	}

	void Application::stop()
	{
		running = false;
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


