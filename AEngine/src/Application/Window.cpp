#include "AEngine/Application/Window.hpp"
#include "AEngine/Exception/InitializationException.hpp"

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace aengine
{
    Window::Window(int width, int height, const char* title, bool fullScreen)
    {
        InitGLFW();

        // If computer doesn't support OpenGL 3.3 don't create window
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_GlfwWindow = glfwCreateWindow(width, height, title, fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
        if (m_GlfwWindow == NULL)
        {
            ThrowInitializationException("Failed to create window! Check your OpenGL version (at least OpenGL 3.3 required)!");
        }
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_GlfwWindow);
    }
    
    bool Window::IsOpen() const noexcept
    {
        return glfwWindowShouldClose(m_GlfwWindow) == 0;
    }

    void Window::Clear() const noexcept
    {
        glClearColor(0.0f, 0.f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::SwapBuffers() const noexcept
    {
        glfwSwapBuffers(m_GlfwWindow);
    }

    void Window::PollEvents() const noexcept
    {
        glfwPollEvents();
    }

    int Window::Width() const noexcept
    {
        int w, h;
        glfwGetWindowSize(m_GlfwWindow, &w, &h);
        return w;
    }
    int Window::Height() const noexcept
    {
        int w, h;
        glfwGetWindowSize(m_GlfwWindow, &w, &h);
        return h;
    }
    glm::ivec2 Window::WindowSize() const noexcept
    {
        glm::ivec2 size;
        glfwGetWindowSize(m_GlfwWindow, &size.x, &size.y);
        return size;
    }


    // Static initialization functions and variables
    bool Window::glfwInitialized = false;
    bool Window::gladInitialized = false;

    void Window::InitGLFW()
    {
        if (!glfwInitialized)
        {
            if (!glfwInit())
            {
                ThrowInitializationException("Failed to initialize GLFW!");
                return;
            }

            glfwInitialized = true;
        }
    }

    void Window::TerminateGLFW()
    {
        if (glfwInitialized)
        {
            glfwTerminate();
            glfwInitialized = false;
        }
    }

    void Window::InitGLAD()
    {
        if (!gladInitialized)
        {
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                ThrowInitializationException("Failed to initialize GLAD!");
                return;
            }

            gladInitialized = true;
        }
    }
}
