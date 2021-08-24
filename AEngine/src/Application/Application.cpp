#include "AEngine/Application/Application.hpp"
#include "AEngine/Input/Input.hpp"
#include "AEngine/Graphics/Renderer2D.hpp"
#include "AEngine/Exception/OpenGLException.hpp"
#include "AEngine/Time.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace aengine
{
    Application::Application(const AppConfig& config) 
    {
        m_Window = new Window(config.scrWidth, config.scrHeight, config.title, config.fullScreen);
        if (config.vSync) glfwSwapInterval(1);

        SetEventListener(this);
        Input::mEventSystem = &mEventSystem;
        Renderer2D::Init();

        // Enable blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Application::~Application() 
    {
        Renderer2D::Shutdown();
        Window::TerminateGLFW();
    }

    void Application::Run()
    {
        // Run start method before first frame
        Start();

        // Main loop
        while(m_Window->IsOpen())
        {
            mEventSystem.kbd.Flush();
            m_Window->PollEvents();
            m_Window->Clear();

            // TODO: Pass current camera's matrix to renderer
            // TODO: Begin and flush renderer here

            Update();

            m_Window->SwapBuffers();

            Renderer2D::ResetStats();
            
            Time::Update();

            // Check OpenGL errors
            GLenum errCode = glGetError();
            if (errCode)
                ThrowOpenGLException(errCode);
        }

        Dispose();
    }

    void Application::Start() { }
    void Application::Update() { }
    void Application::Dispose() { }

    // Updates viewport on window resized
    void Application::OnResize(int width, int height) 
    {
        glViewport(0, 0, width, height);
    }

    GLFWwindow* Application::GetGLFWwindow()
    {
        return m_Window->m_GlfwWindow;
    }
}
