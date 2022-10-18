
#include "window.h"

#include <app/input/input.h>
#include <app/input/event.h>

#include <core/debug/debug.h>
#include <core/graphics/core/renderer.h>

#include <app/core.h>

namespace Desdun
{

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
        
        glfwSetWindowUserPointer(WindowObject, (void*)this);

        glfwSetWindowCloseCallback(WindowObject,
            [](GLFWwindow* window)
            {
                Window& ActiveWindow = *(Window*)glfwGetWindowUserPointer(window);
                Application::GetApplication()->End();
            });

        glfwSetWindowSizeCallback(WindowObject,
            [](GLFWwindow* window, int Width, int Height)
            {
                Window* ActiveWindow = (Window*)glfwGetWindowUserPointer(window);
                ActiveWindow->Size = glm::uvec2(Width, Height);

                WindowEvent NewEvent = {};

                NewEvent.Size = ActiveWindow->Size;
                NewEvent.Focused = ActiveWindow->IsFocused;

                Application::GetApplication()->PushWindowEvent(NewEvent);
            });

        glfwSetWindowFocusCallback(WindowObject,
            [](GLFWwindow* window, int Focused)
            {
                Window* ActiveWindow = (Window*)glfwGetWindowUserPointer(window);

                WindowEvent NewEvent{};

                NewEvent.Size = ActiveWindow->Size;
                NewEvent.Focused = (bool)Focused;

                Application::GetApplication()->PushWindowEvent(NewEvent);
            });

        glfwSetScrollCallback(WindowObject,
            [](GLFWwindow* window, double xOffset, double yOffset)
            {
                InputEvent NewEvent{};

                NewEvent.InputState = Input::State::Changed;
                NewEvent.InputType = Input::Type::Scrolling;

                NewEvent.Delta = glm::vec3(xOffset, yOffset, 0.0);

                Application::GetApplication()->PushInputEvent(NewEvent);
            });

        glfwSetCursorPosCallback(WindowObject,
            [](GLFWwindow* window, double xPos, double yPos)
            {
                InputEvent NewEvent{};

                NewEvent.InputState = Input::State::Changed;
                NewEvent.InputType = Input::Type::Mouse;

                NewEvent.Position = glm::vec3((int)xPos, (int)yPos, 0);

                //Debug::Log(std::to_string(xPos) + " " + std::to_string(yPos));

                Application::GetApplication()->PushInputEvent(NewEvent);
            });

        glfwSetMouseButtonCallback(WindowObject,
            [](GLFWwindow* window, int button, int action, int mods)
            {
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

                Application::GetApplication()->PushInputEvent(NewEvent);
            });

        glfwSetKeyCallback(WindowObject,
            [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                InputEvent NewEvent{};

                NewEvent.InputType = Input::Type::Keyboard;
                NewEvent.KeyCode = (Input::KeyCode)key;

                switch (action)
                {
                case GLFW_PRESS: NewEvent.InputState = Input::State::Begin; break;
                case GLFW_RELEASE: NewEvent.InputState = Input::State::End; break;
                }

                Application::GetApplication()->PushInputEvent(NewEvent);
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
        Renderer::Clear();
    }

    void Window::Update()
    {
        glfwSwapBuffers(WindowObject);
        glfwPollEvents();
    }
}