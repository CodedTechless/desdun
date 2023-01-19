
#include <GL/glew.h>
#include <glfw3.h>

#include <app/debug/debug.h>

#include <graphics/renderer.h>
#include <resource/resource.hpp>

#include <app/runtime/runtime_info.h>
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
		
        Runtime::Start();

        GameWindow = new Window("Desecrated Dungeons", { 800, 600 });
        Renderer::Start();


        /*
        ImGuiLayer = new ImGuiLayer(ImGuiIniFileName);
        Layers.PushOverlay(a_ImGuiLayer);
        */
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
                    a_Layer->OnGameStep(Accumulator);
                }

                Accumulator -= GameSpeed;
            }

            StepInterpFrac = Accumulator / GameSpeed;
            
            GameWindow->Clear();

            for (auto* Layer : GameLayers)
            {
                Layer->OnFrameUpdate(FrameTime);
            }

            GameWindow->Update();
		}
	}

	void Application::End()
	{
		Running = false;
	}

    void Application::PushInputEvent(const InputEvent& inputEvent)
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

    void Application::PushWindowEvent(const WindowEvent& windowEvent)
    {
        for (auto* Layer : GameLayers)
        {
            Layer->OnWindowEvent(windowEvent);
        }
    }
}


