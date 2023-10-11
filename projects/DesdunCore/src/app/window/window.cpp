
#include <app/app.hpp>
#include <app/debug/debug.hpp>
#include <graphics/render/renderer.hpp>

#include "window.hpp"
#include "input.hpp"

namespace Desdun
{

    Window::Window(const std::string& title, Vector2i windowSize)
        : title(title), size(windowSize)
    {
        glfwSetErrorCallback(Debug::GLFWMessage);

        if (glfwInit() != GL_TRUE)
            assert(false);
        
        // preferably be on opengl 4.2 but not the end of the world

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
        

        windowObject = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
        if (windowObject == nullptr)
        {
            glfwTerminate();
            assert(false);
        }

        glfwMakeContextCurrent(windowObject);
        if (glewInit() != GLEW_OK)
            assert(false);


        // set up all of the input callbacks here to interface with the input system
        
        glfwSetWindowUserPointer(windowObject, (void*)this);

        glfwSetWindowCloseCallback(windowObject,
            [](GLFWwindow* window)
            {
                Application::get()->stop();
            });

        glfwSetWindowContentScaleCallback(windowObject,
            [](GLFWwindow* window, float xScale, float yScale)
            {
                Window* activeWindow = (Window*)glfwGetWindowUserPointer(window);
                activeWindow->dpiScale = Vector2(xScale, yScale);

                Application::get()->pushWindowEvent({ activeWindow });
            });

        glfwSetWindowSizeCallback(windowObject,
            [](GLFWwindow* window, int Width, int Height)
            {
                Window* activeWindow = (Window*)glfwGetWindowUserPointer(window);
                activeWindow->size = Vector2i(Width, Height);

                Application::get()->pushWindowEvent({ activeWindow });
            });

        glfwSetWindowFocusCallback(windowObject,
            [](GLFWwindow* window, int Focused)
            {
                Window* activeWindow = (Window*)glfwGetWindowUserPointer(window);
                activeWindow->isFocused = (bool)Focused;

                Application::get()->pushWindowEvent({ activeWindow });
            });

        glfwSetScrollCallback(windowObject,
            [](GLFWwindow* window, double xOffset, double yOffset)
            {
                Input::Event newEvent;

                for (auto& [name, action] : Input::registeredActions)
                {
                    if (action.type == Input::Type::MouseScrolling && action.state == Input::State::Changed)
                    {
                        newEvent.isRegistered = true;
                        newEvent.action = action;

                        break;
                    }
                }

                if (!newEvent.isRegistered)
                {
                    newEvent.action = {};
                    newEvent.action.state = Input::State::Changed;
                    newEvent.action.type = Input::Type::MouseScrolling;
                }

                newEvent.action.delta = Vector3(xOffset, yOffset, 0.f);

                Application::get()->pushInputEvent(newEvent);
            });

        glfwSetCursorPosCallback(windowObject,
            [](GLFWwindow* window, double xPos, double yPos)
            {
                Input::Event newEvent;

                for (auto& [name, action] : Input::registeredActions)
                {
                    if (action.type == Input::Type::Mouse && action.state == Input::State::Changed)
                    {
                        newEvent.isRegistered = true;
                        newEvent.action = action;

                        break;
                    }
                }

                if (!newEvent.isRegistered)
                {
                    newEvent.action = {};
                    newEvent.action.state = Input::State::Changed;
                    newEvent.action.type = Input::Type::Mouse;
                }

                newEvent.action.position = Vector3(xPos, yPos, 0.f);

                Application::get()->pushInputEvent(newEvent);
            });

        glfwSetMouseButtonCallback(windowObject,
            [](GLFWwindow* window, int button, int action, int mods)
            {
                Input::MouseCode mouseButton = (Input::MouseCode)button;
                Input::State state = Input::State::None;

                switch (action)
                {
                    case GLFW_PRESS: state = Input::State::Begin; break;
                    case GLFW_RELEASE: state = Input::State::End; break;
                }

                Input::Event newEvent;

                for (auto& [name, action] : Input::registeredActions)
                {
                    if (action.type == Input::Type::Mouse && action.state == state && action.mouseButton == mouseButton)
                    {
                        newEvent.isRegistered = true;
                        newEvent.action = action;

                        break;
                    }
                }

                if (!newEvent.isRegistered)
                {
                    newEvent.action = {};
                    newEvent.action.mouseButton = mouseButton;
                    newEvent.action.state = state;
                    newEvent.action.type = Input::Type::Mouse;
                }

                newEvent.action.position = Vector3(Input::getMousePosition(), 0.f);

                Application::get()->pushInputEvent(newEvent);
            });

        glfwSetKeyCallback(windowObject,
            [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                Input::KeyCode keyCode = (Input::KeyCode)key;
                Input::State state = Input::State::None;

                switch (action)
                {
                    case GLFW_PRESS: state = Input::State::Begin; break;
                    case GLFW_RELEASE: state = Input::State::End; break;
                }

                Input::Event newEvent;
                
                for (auto& [name, action] : Input::registeredActions)
                {
                    if (action.type == Input::Type::Keyboard && action.state == state && action.keyCode == keyCode)
                    {
                        newEvent.isRegistered = true;
                        newEvent.action = action;
                        
                        break;
                    }
                }

                if (!newEvent.isRegistered)
                {
                    newEvent.action = {};
                    newEvent.action.keyCode = keyCode;
                    newEvent.action.state = state;
                    newEvent.action.type = Input::Type::Keyboard;
                }

                Application::get()->pushInputEvent(newEvent);
            });

        glfwGetWindowContentScale(windowObject, &dpiScale.x, &dpiScale.y);
        glfwGetWindowSize(windowObject, &size.x, &size.y);
    }

    Window::~Window()
    {
        glfwDestroyWindow(windowObject);
    }

    void Window::setVsyncEnabled(bool Enabled)
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

    void Window::update()
    {
        glfwSwapBuffers(windowObject);
        glfwPollEvents();
    }
}