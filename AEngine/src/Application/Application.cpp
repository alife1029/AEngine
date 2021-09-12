#include "AEngine/Application/Application.hpp"
#include "AEngine/Application/FileDialogs.hpp"
#include "AEngine/Input/Input.hpp"
#include "AEngine/Graphics/Renderer2D.hpp"
#include "AEngine/Exception/OpenGLException.hpp"
#include "AEngine/Utils/Time.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>

namespace aengine
{
    Application::Application(const AppConfig& config) 
    {
        m_Window = new Window(config.scrWidth, config.scrHeight, config.title, config.fullScreen);
        if (config.vSync) glfwSwapInterval(1);

        FileDialog::window = m_Window->m_GlfwWindow;

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
            mEventSystem.Flush();
            m_Window->PollEvents();

            if (focused)
            {
                m_Window->Clear();

                // TODO: Pass current camera's matrix to renderer
                // TODO: Begin and flush renderer here

                Update();

                m_Window->SwapBuffers();

                Renderer2D::ResetStats();

                // Check OpenGL errors
                GLenum errCode = glGetError();
                if (errCode)
                    ThrowOpenGLException(errCode);
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }
            
            Time::Update();
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

    void Application::OnFocus(bool focused)
    {
        this->focused = focused;
    }

    GLFWwindow* Application::GetGLFWwindow()
    {
        return m_Window->m_GlfwWindow;
    }

    bool Application::IsFocused()
    {
        return focused;
    }
}
