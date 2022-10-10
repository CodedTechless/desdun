
#include "window.h"

#include <core/debug/debug.h>
#include <core/input/input.h>
#include <core/input/event.h>

#include <core/graphics/interface.h>

#include <game/core.h>

namespace Desdun
{

    struct UserPointerInfo
    {
        Game* GameInstance;
        Window* ActiveWindow;
    };

    Window::Window(const std::string& title, Vector2 size)
        : Title(title), Size(size)
    {
        glfwSetErrorCallback(Debug::GLFWMessage);

        if (glfwInit() != GL_TRUE)
            assert(false);
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        WindowObject = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
        if (WindowObject == nullptr)
        {
            glfwTerminate();
            assert(false);
        }

        glfwMakeContextCurrent(WindowObject);
        if (glewInit() != GLEW_OK)
            assert(false);

        //Debug::Log("Created window (" + std::to_string(aSize.x) + ", " + std::to_string(aSize.y) + ")", "Application");

        // Set up all the input callbacks.
        UserPointerInfo* userPointerInfo = new UserPointerInfo({ Game::GetInstance(), this });

        glfwSetWindowUserPointer(WindowObject, (void*)userPointerInfo);

        glfwSetWindowCloseCallback(WindowObject,
            [](GLFWwindow* window)
            {
                UserPointerInfo& PointerInfo = *(UserPointerInfo*)glfwGetWindowUserPointer(window);
                PointerInfo.GameInstance->End();
            });

        glfwSetWindowSizeCallback(WindowObject,
            [](GLFWwindow* window, int Width, int Height)
            {
                UserPointerInfo& PointerInfo = *(UserPointerInfo*)glfwGetWindowUserPointer(window);
                PointerInfo.ActiveWindow->Size = glm::uvec2(Width, Height);

                WindowEvent NewEvent = {};

                NewEvent.Size = PointerInfo.ActiveWindow->Size;
                NewEvent.Focused = PointerInfo.ActiveWindow->IsFocused;

                PointerInfo.GameInstance->PushWindowEvent(NewEvent);
            });

        glfwSetWindowFocusCallback(WindowObject,
            [](GLFWwindow* window, int Focused)
            {
                UserPointerInfo& PointerInfo = *(UserPointerInfo*)glfwGetWindowUserPointer(window);

                WindowEvent NewEvent{};

                NewEvent.Size = PointerInfo.ActiveWindow->Size;
                NewEvent.Focused = (bool)Focused;

                PointerInfo.GameInstance->PushWindowEvent(NewEvent);
            });

        glfwSetScrollCallback(WindowObject,
            [](GLFWwindow* window, double xOffset, double yOffset)
            {
                UserPointerInfo& PointerInfo = *(UserPointerInfo*)glfwGetWindowUserPointer(window);

                InputEvent NewEvent{};

                NewEvent.InputState = Input::State::Changed;
                NewEvent.InputType = Input::Type::Scrolling;

                NewEvent.Delta = glm::vec3(xOffset, yOffset, 0.0);

                PointerInfo.GameInstance->PushInputEvent(NewEvent);
            });

        glfwSetCursorPosCallback(WindowObject,
            [](GLFWwindow* window, double xPos, double yPos)
            {
                UserPointerInfo& PointerInfo = *(UserPointerInfo*)glfwGetWindowUserPointer(window);

                InputEvent NewEvent{};

                NewEvent.InputState = Input::State::Changed;
                NewEvent.InputType = Input::Type::Mouse;

                NewEvent.Position = glm::vec3((int)xPos, (int)yPos, 0);

                //Debug::Log(std::to_string(xPos) + " " + std::to_string(yPos));

                PointerInfo.GameInstance->PushInputEvent(NewEvent);
            });

        glfwSetMouseButtonCallback(WindowObject,
            [](GLFWwindow* window, int button, int action, int mods)
            {
                UserPointerInfo& PointerInfo = *(UserPointerInfo*)glfwGetWindowUserPointer(window);

                InputEvent NewEvent{};

                NewEvent.InputType = Input::Type::Mouse;
                NewEvent.MouseCode = (Input::MouseCode)button;

                double X, Y;
                glfwGetCursorPos(window, &X, &Y);

                NewEvent.Position = glm::vec3((int)X, (int)Y, 0);

                switch (action)
                {
                case GLFW_PRESS: NewEvent.InputState = Input::State::Begin; break;
                case GLFW_RELEASE: NewEvent.InputState = Input::State::End; break;
                }

                PointerInfo.GameInstance->PushInputEvent(NewEvent);
            });

        glfwSetKeyCallback(WindowObject,
            [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                UserPointerInfo& PointerInfo = *(UserPointerInfo*)glfwGetWindowUserPointer(window);

                InputEvent NewEvent{};

                NewEvent.InputType = Input::Type::Keyboard;
                NewEvent.KeyCode = (Input::KeyCode)key;

                switch (action)
                {
                case GLFW_PRESS: NewEvent.InputState = Input::State::Begin; break;
                case GLFW_RELEASE: NewEvent.InputState = Input::State::End; break;
                }

                PointerInfo.GameInstance->PushInputEvent(NewEvent);
            });
    }

    Window::~Window()
    {
        glfwDestroyWindow(WindowObject);
    }

    void Window::SetVsyncEnabled(bool Enabled)
    {
        if (Enabled)
        {
            Debug::Log("Vertical sync: Enabled", "Window");
            glfwSwapInterval(1);
        }
        else
        {
            Debug::Log("Vertical sync: Disabled", "Window");
            glfwSwapInterval(0);
        }
    }

    void Window::Clear()
    {
        RenderInterface::Clear();
    }

    void Window::Update()
    {
        glfwSwapBuffers(WindowObject);
        glfwPollEvents();
    }
}