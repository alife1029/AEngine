#include "AEngine/Input/EventSystem.hpp"
#include "AEngine/Application/Application.hpp"

#include <GLFW/glfw3.h>

namespace aengine
{
    Keyboard EventSystem::kbd = Keyboard();
    void EventSystem::OnResize(int width, int height) { }
    void EventSystem::SetEventListener(Application* appInstance)
    {
        GLFWcallbacks::eventSystemInstance = this;
        glfwSetFramebufferSizeCallback(appInstance->GetGLFWwindow(), GLFWcallbacks::framebuffer_size_callback);
        glfwSetKeyCallback(appInstance->GetGLFWwindow(), GLFWcallbacks::key_callback);
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
}
