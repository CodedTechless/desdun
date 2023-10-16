
#include <app/debug/debug.hpp>
#include <resources/resource.hpp>
#include <runtime/runtime.hpp>
#include <graphics/render/renderer.hpp>
#include <objects/index.hpp>

#include <resources/types/text/font_face.hpp>
#include <imgui/imgui.h>

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
        delete gameWindow;

        stop();
        gameLayers.clear();
        delete renderer;

        // terminate libraries
        FT_Done_FreeType(*FontFace::library);
        glfwTerminate();
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

        uint frames = 0;
        float frameTime = 0.f;

        while (running)
        {
            float NewTime = (float)glfwGetTime();
            float FrameTime = std::min(NewTime - CurrentTime, 0.25f);
            frameDelta = NewTime - CurrentTime;
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

            frames++;
            frameTime += frameDelta;

            if (frameTime > 1.f)
            {
                frameTime -= 1.f;

                frameRate = frames;
                frames = 0.f;
            }
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

    void Application::showDebug()
    {
        ImGui::Begin("Debugger");
        {
            auto* app = Application::get();

            if (ImGui::CollapsingHeader("Peformance"))
            {
                if (ImGui::BeginTable("performanceTable", 2))
                {
                    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
                    ImGui::TableSetupColumn("Stat", ImGuiTableColumnFlags_WidthFixed);
                    ImGui::TableHeadersRow();

                    ImGui::TableNextColumn();
                    ImGui::Text("FPS");
                    ImGui::TableNextColumn();
                    ImGui::Text(std::to_string((uint)frameRate).c_str());

                    ImGui::TableNextColumn();
                    ImGui::Text("Frame time");
                    ImGui::TableNextColumn();
                    ImGui::Text((std::to_string(frameDelta * 1000.f) + "ms").c_str());

                    ImGui::EndTable();
                }
            };

            if (ImGui::CollapsingHeader("Graphics"))
            {
                if (ImGui::BeginTable("graphicsTable", 2))
                {
                    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
                    ImGui::TableSetupColumn("Stat", ImGuiTableColumnFlags_WidthFixed);
                    ImGui::TableHeadersRow();

                    auto frameData = getRenderer()->performance();

                    ImGui::TableNextColumn();
                    ImGui::Text("Draw calls");
                    ImGui::TableNextColumn();
                    ImGui::Text(std::to_string(frameData.drawCalls).c_str());

                    ImGui::TableNextColumn();
                    ImGui::Text("Vertex count");
                    ImGui::TableNextColumn();
                    ImGui::Text(std::to_string(frameData.vertexCount).c_str());

                    auto* window = Application::get()->getPrimaryWindow();
                    auto size = window->getSize();

                    ImGui::TableNextColumn();
                    ImGui::Text("Window resolution");
                    ImGui::TableNextColumn();
                    ImGui::Text(std::string(std::to_string((uint)size.x) + "x" + std::to_string((uint)size.y)).c_str());

                    ImGui::EndTable();
                }
            };

            if (ImGui::CollapsingHeader("Layer Stack"))
            {
                for (auto* layer : app->gameLayers)
                {
                    ImGui::Text(layer->name().c_str());
                }
            }

            if (ImGui::CollapsingHeader("Resources"))
            {
                for (auto& [typeIndex, resourceCollection] : Resource::getResources())
                {
                    if (ImGui::TreeNodeEx(typeIndex.name(), ImGuiTreeNodeFlags_OpenOnArrow))
                    {
                        for (auto& [path, _] : resourceCollection)
                        {
                            ImGui::Text(path.c_str());
                        }

                        ImGui::TreePop();
                    }
                }
            };

        }
        ImGui::End();

    }
}


