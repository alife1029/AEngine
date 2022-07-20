#include "AEngine/Application/Application.hpp"
#include "AEngine/Application/FileDialogs.hpp"
#include "AEngine/Input/Input.hpp"
#include "AEngine/Graphics/Renderer2D.hpp"
#include "AEngine/Graphics/Renderer2DStatic.hpp"
#include "AEngine/Graphics/TextRenderer.hpp"
#include "AEngine/Graphics/FontManager.hpp"
#include "AEngine/Graphics/RendererStat.hpp"
#include "AEngine/Exception/OpenGLException.hpp"
#include "AEngine/Utils/Time.hpp"
#include "AEngine/Utils/Logger.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <thread>
#include <chrono>

namespace aengine
{
    Application::Application(const AppConfig& config) 
    {
        m_MainCamera = nullptr;
        m_Window = new Window(config.scrWidth, config.scrHeight, config.title, config.fullScreen);
        if (config.vSync) glfwSwapInterval(1);

        FileDialog::window = m_Window->m_GlfwWindow;

        SetEventListener(this);
        Input::mEventSystem = &mEventSystem;
        
        // Initialize renderers
        Renderer2D::Init();
        Renderer2DStatic::Init();
        TextRenderer::Initialize(m_Window);

        // Initialize ImGui
        #ifdef _DEBUG
        IMGUI_CHECKVERSION();
        #endif
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(GetGLFWwindow(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        // Enable blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Enable depth testing
        //glEnable(GL_DEPTH_TEST);
    }

    Application::~Application() 
    {
        // Dispose ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        FontManager::Dispose();
        TextRenderer::Shutdown();
        Renderer2D::Shutdown();
        Renderer2DStatic::Shutdown();
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

            m_Window->Clear();

            if (m_MainCamera != nullptr) m_MainCamera->Update();

            Renderer2D::Begin(m_MainCamera != nullptr ? m_MainCamera->Combined() : glm::mat4(1.0f));
            TextRenderer::Begin();

            // ImGui new frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            Update();

            Renderer2DStatic::RenderScene(m_MainCamera != nullptr ? m_MainCamera->Combined() : glm::mat4(1.0f));
            Renderer2D::End();
            Renderer2D::Flush();
            TextRenderer::End();
            RendererStat::Reset();

            // Render ImGui draw data
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            m_Window->SwapBuffers();

            // Check OpenGL errors
            GLenum errCode = glGetError();
            if (errCode && focused)
                ThrowOpenGLException(errCode);
            
            Time::Update();
        }

        Dispose();
    }

    void Application::BindMainCamera(OrthographicCamera* camera) noexcept
    {
        m_MainCamera = camera;
    }
    OrthographicCamera* Application::GetMainCamera() const noexcept
    {
        return m_MainCamera;
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

    Window* Application::GetWindow() const noexcept
    {
        return m_Window;
    }

    GLFWwindow* Application::GetGLFWwindow() const noexcept
    {
        return m_Window->m_GlfwWindow;
    }

    bool Application::IsFocused() const noexcept
    {
        return focused;
    }
}
