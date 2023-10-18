
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

        // initialise script engine
        scriptEngine = new LuaScriptEngine();

        auto& state = scriptEngine->getState();

        dd_define(Vector2,
            sol::constructors<Vector2(), Vector2(float, float)>(),
            
            "x", &Vector2::x,
            "y", &Vector2::y,

            "magnitude", [](Vector2& vec) -> float
            {
                return glm::length(vec);
            },

            "abs", [](Vector2& vec) -> Vector2
            {
                return glm::abs(vec);
            },

            sol::meta_function::addition, sol::overload(
                [](Vector2 A, Vector2 B) -> Vector2 { return A + B; },
                [](Vector2 A, float B) -> Vector2 { return A + B; },
                [](float A, Vector2 B) -> Vector2 { return A + B; }
            ),
            sol::meta_function::subtraction, sol::overload(
                [](Vector2 A, Vector2 B) -> Vector2 { return A - B; },
                [](Vector2 A, float B) -> Vector2 { return A - B; },
                [](float A, Vector2 B) -> Vector2 { return A - B; }
            ),
            sol::meta_function::multiplication, sol::overload(
                [](Vector2 A, Vector2 B) -> Vector2 { return A * B; },
                [](Vector2 A, float B) -> Vector2 { return A * B; },
                [](float A, Vector2 B) -> Vector2 { return A * B; }
            ),
            sol::meta_function::division, sol::overload(
                [](Vector2 A, Vector2 B) -> Vector2 { return A / B; },
                [](Vector2 A, float B) -> Vector2 { return A / B; },
                [](float A, Vector2 B) -> Vector2 { return A / B; }
            ),

            sol::meta_function::unary_minus, [](Vector2 A) -> Vector2 { return -A; }

        );

        dd_define(Vector3,
            sol::constructors<Vector3(), Vector3(float, float, float)>(),

            "x", & Vector3::x,
            "y", & Vector3::y,
            "z", & Vector3::z,

            "magnitude", [](Vector3& vec) -> float
            {
                return glm::length(vec);
            },

            "abs", [](Vector3& vec) -> Vector3
            {
                return glm::abs(vec);
            },

            sol::meta_function::addition, sol::overload(
                [](Vector3 A, Vector3 B) -> Vector3 { return A + B; },
                [](Vector3 A, float B) -> Vector3 { return A + B; },
                [](float A, Vector3 B) -> Vector3 { return A + B; }
            ),
            sol::meta_function::subtraction, sol::overload(
                [](Vector3 A, Vector3 B) -> Vector3 { return A - B; },
                [](Vector3 A, float B) -> Vector3 { return A - B; },
                [](float A, Vector3 B) -> Vector3 { return A - B; }
            ),
            sol::meta_function::multiplication, sol::overload(
                [](Vector3 A, Vector3 B) -> Vector3 { return A * B; },
                [](Vector3 A, float B) -> Vector3 { return A * B; },
                [](float A, Vector3 B) -> Vector3 { return A * B; }
            ),
            sol::meta_function::division, sol::overload(
                [](Vector3 A, Vector3 B) -> Vector3 { return A / B; },
                [](Vector3 A, float B) -> Vector3 { return A / B; },
                [](float A, Vector3 B) -> Vector3 { return A / B; }
            ),

            sol::meta_function::unary_minus, [](Vector3 A) -> Vector3 { return -A; }
        );

        dd_define(Vector4, 
            sol::constructors<Vector4(), Vector4(float, float, float, float)>(),

            "x", &Vector4::x,
            "y", &Vector4::y,
            "z", &Vector4::z,
            "w", &Vector4::w,

            "magnitude", [](Vector4& vec) -> float
            { 
                return glm::length(vec); 
            },

            "abs", [](Vector4& vec) -> Vector4
            { 
                return glm::abs(vec);
            },

            sol::meta_function::addition, sol::overload(
                [](Vector4 A, Vector4 B) -> Vector4 { return A + B; },
                [](Vector4 A, float B) -> Vector4 { return A + B; },
                [](float A, Vector4 B) -> Vector4 { return A + B; }
            ),
            sol::meta_function::subtraction, sol::overload(
                [](Vector4 A, Vector4 B) -> Vector4 { return A - B; },
                [](Vector4 A, float B) -> Vector4 { return A - B; },
                [](float A, Vector4 B) -> Vector4 { return A - B; }
            ),
            sol::meta_function::multiplication, sol::overload(
                [](Vector4 A, Vector4 B) -> Vector4 { return A * B; },
                [](Vector4 A, float B) -> Vector4 { return A * B; },
                [](float A, Vector4 B) -> Vector4 { return A * B; }
            ),
            sol::meta_function::division, sol::overload(
                [](Vector4 A, Vector4 B) -> Vector4 { return A / B; },
                [](Vector4 A, float B) -> Vector4 { return A / B; },
                [](float A, Vector4 B) -> Vector4 { return A / B; }
            ),

            sol::meta_function::unary_minus, [](Vector4 A) -> Vector4 { return -A; }
        );

        dd_define_type(Object,
            sol::no_constructor,
            "parent", sol::property(&Object::getParent, &Object::setParent),
            "clone", &Object::clone,
            "scene", sol::property(&Object::getScene),
            "instanceId", sol::property(&Object::getInstanceId)
        );
        
        dd_define_type_inheritence(Entity2D, { Runtime::get<Object>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Object>(),

            "zIndex", &Entity2D::zIndex,
            "visible", &Entity2D::visible,
            "interpolate", &Entity2D::interpolate,

            "position", sol::property(&Entity2D::getPosition, &Entity2D::setPosition),
            "scale", sol::property(&Entity2D::getScale, &Entity2D::setScale),
            "rotation", sol::property(&Entity2D::getRotation, &Entity2D::setRotation),

            "globalPosition", sol::property(&Entity2D::getGlobalPosition),
            "globalScale", sol::property(&Entity2D::getGlobalScale),
            "globalRotation", sol::property(&Entity2D::getGlobalRotation),

            "translate", &Entity2D::translate,
            "resize", &Entity2D::resize,
            "rotate", &Entity2D::rotate
        );

        // todo: figure out a way to get these values into the inspector
        // for now we can just pull it through lua but that'd be inefficient due to marshalling
        dd_define_type_inheritence(Camera2D, { Runtime::get<Entity2D>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Entity2D>(),

            "subject", &Camera2D::subject,
            "offset", &Camera2D::offset,

            "targetViewportSize", &Camera2D::targetViewportSize,
            "smoothFollow", &Camera2D::smoothFollow,
            "adjustToAspectRatio", &Camera2D::adjustToAspectRatio,

            "getMouseInWorld", &Camera2D::getMouseInWorld
        );

        dd_define_type_inheritence(SoundEmitter2D, { Runtime::get<Entity2D>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Entity2D>()
        );

        dd_define_type_inheritence(ParticleEmitter2D, { Runtime::get<Entity2D>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Entity2D>()
        );

        dd_define_type_inheritence(Sprite, { Runtime::get<Entity2D>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Entity2D>()
        );

        dd_define_type_inheritence(AnimatedSprite, { Runtime::get<Sprite>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Sprite>()
        );

        dd_define_type_inheritence(TileMap, { Runtime::get<Entity2D>() },
            sol::no_constructor,
            sol::base_classes, sol::bases<Entity2D>()
        );

        // Start renderer
        auto* textureShader = Resource::fetch<Shader>("shaders:tex/tex.tres");
        renderer = new Renderer(textureShader);

        // push imgui layer
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
                frames = 0;
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
    }

    LuaScriptEngine* Application::getScriptEngine() const
    {
        return scriptEngine;
    }
    
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

    ImGuiLayer* Application::getImGuiLayer() const
    {
        return imguiLayer;
    }

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


