#include "AEngine/Input/EventSystem.hpp"
#include "AEngine/Application/Application.hpp"

#include <GLFW/glfw3.h>

namespace aengine
{
    Keyboard EventSystem::kbd = Keyboard();
    Mouse EventSystem::mouse = Mouse();
    void EventSystem::OnResize(int width, int height) { }
    void EventSystem::SetEventListener(Application* appInstance)
    {
        GLFWcallbacks::eventSystemInstance = this;

        // GLFW Callbacks
        glfwSetFramebufferSizeCallback(appInstance->GetGLFWwindow(), GLFWcallbacks::framebuffer_size_callback);
        glfwSetKeyCallback(appInstance->GetGLFWwindow(), GLFWcallbacks::key_callback);
        glfwSetCursorPosCallback(appInstance->GetGLFWwindow(), GLFWcallbacks::cursor_position_callback);
        glfwSetMouseButtonCallback(appInstance->GetGLFWwindow(), GLFWcallbacks::mouse_button_callback);
        glfwSetScrollCallback(appInstance->GetGLFWwindow(), GLFWcallbacks::scroll_callback);
    }
    void EventSystem::Flush()
    {
        kbd.Flush();
        mouse.Flush();
    }

    EventSystem* EventSystem::GLFWcallbacks::eventSystemInstance = nullptr;
    void EventSystem::GLFWcallbacks::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        eventSystemInstance->OnResize(width, height);
    }
    void EventSystem::GLFWcallbacks::key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods)
    {
        switch (action)
        {
        case GLFW_PRESS:
            eventSystemInstance->kbd.OnKeyPress(key);
            break;
        case GLFW_RELEASE:
            eventSystemInstance->kbd.OnKeyRelease(key);
            break;
        }
    }

    // Mouse callbacks
    void EventSystem::GLFWcallbacks::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        eventSystemInstance->mouse.OnCursorMoved(xpos, ypos);
    }
    void EventSystem::GLFWcallbacks::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        switch (action)
        {
        case GLFW_PRESS:
            eventSystemInstance->mouse.OnButtonPress(button);
            break;
        case GLFW_RELEASE:
            eventSystemInstance->mouse.OnButtonRelease(button);
            break;
        }
    }
    void EventSystem::GLFWcallbacks::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        eventSystemInstance->mouse.OnScrolled(xoffset, yoffset);
    }
}
