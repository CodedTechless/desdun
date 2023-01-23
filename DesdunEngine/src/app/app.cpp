


#include <app/debug/debug.h>

#include <graphics/renderer.h>
#include <resource/resource.hpp>

#include <app/runtime.h>
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
	Application* Application::AppObject = nullptr;

    ResourceMap Resource::Resources = {};

	Application::Application()
	{
		AppObject = this;
		
        Debug::Log("Starting base runtime");
        Runtime::Start();

        GameWindow = new Window("Desecrated Dungeons", { 800, 600 });
        Debug::Log("Starting renderer");
        Renderer::Start();

        Debug::Log("Adding imgui layer");

        imguiLayer = new ImGuiLayer("imgui.ini");
        GameLayers.PushOverlay(imguiLayer);
	}

	Application::~Application()
	{
        delete GameWindow;
        Renderer::Stop();
	}

	void Application::Run()
	{
		if (Running)
		{
            return;
		}

		Running = true;
        float Time = 0.f;
        float CurrentTime = (float)glfwGetTime();
        float Accumulator = 0.f;

        size_t Frames = 0, Updates = 0;

        while (Running)
        {
            float NewTime = (float)glfwGetTime();
            float FrameTime = std::min(NewTime - CurrentTime, 0.25f);
            CurrentTime = NewTime;

            Time += FrameTime;
            Accumulator += FrameTime;

            while (Accumulator >= GameSpeed)
            {
                for (Layer* a_Layer : GameLayers) {
                    a_Layer->onGameStep(Accumulator);
                }

                Accumulator -= GameSpeed;
            }

            StepInterpFrac = Accumulator / GameSpeed;
            
            GameWindow->clear();
            imguiLayer->begin();

            for (auto* Layer : GameLayers)
            {
                Layer->onFrameUpdate(FrameTime);
            }

            imguiLayer->end();
            GameWindow->update();
		}
	}

	void Application::End()
	{
		Running = false;
	}

    void Application::pushInputEvent(Input::Event& event)
    {
        for (auto i = GameLayers.rbegin(); i != GameLayers.rend(); ++i)
        {
            (*i)->onInputEvent(event);

            if (event.absorbed)
                break;
        }
    }

    void Application::pushWindowEvent(const Window::Event& windowEvent)
    {
        for (auto* Layer : GameLayers)
        {
            Layer->onWindowEvent(windowEvent);
        }
    }
}


