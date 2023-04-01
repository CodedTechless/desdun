


#include <app/debug/debug.h>

#include <graphics/renderer.h>
#include <resource/resource.hpp>

#include <runtime/runtime.h>
#include <object/index.hpp>

#include "app.h"

namespace glm
{
    void to_json(json& jsonObject, const glm::vec2& vec)
    {
        jsonObject = {
            { "x", vec.x },
            { "y", vec.y }
        };
    };

    void to_json(json& jsonObject, const glm::vec3& vec)
    {
        jsonObject = {
            { "x", vec.x },
            { "y", vec.y },
            { "z", vec.z }
        };
    };

    void to_json(json& jsonObject, const glm::vec4& vec)
    {
        jsonObject = {
            { "x", vec.x },
            { "y", vec.y },
            { "z", vec.z },
            { "w", vec.w }
        };
    };

    void from_json(const json& j, glm::vec2& vec)
    {
        vec = glm::vec2(
            j.at("x").get<float>(),
            j.at("y").get<float>()
        );
    };

    void from_json(const json& j, glm::vec3& vec)
    {
        vec = glm::vec3(
            j.at("x").get<float>(),
            j.at("y").get<float>(),
            j.at("z").get<float>()
        );
    };

    void from_json(const json& j, glm::vec4& vec)
    {
        vec = glm::vec4(
            j.at("x").get<float>(),
            j.at("y").get<float>(),
            j.at("z").get<float>(),
            j.at("w").get<float>()
        );
    };
}

namespace Desdun
{

    Application* Application::currentApp = nullptr;
    ResourceMap Resource::resources = {};
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

                Runtime::add<PhysicsBody>({ "PhysicsBody", Runtime::get<WorldObject>() });
                {
                    Runtime::add<DynamicBody>({ "DynamicBody", Runtime::get<WorldObject>() });
                    Runtime::add<StaticBody>({ "StaticBody", Runtime::get<WorldObject>() });
                }

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


