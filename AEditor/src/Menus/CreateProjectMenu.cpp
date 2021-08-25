#include "CreateProjectMenu.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using namespace aengine;

CreateProjectMenu::CreateProjectMenu(Application* app) : Menu(app) { }

void CreateProjectMenu::Start()
{
    mWnd = mApp->GetGLFWwindow();
    glfwSetWindowSize(mWnd, 540, 305);
}

void CreateProjectMenu::Update()
{
    // Init UI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    RenderUI();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ProcessInputs();
}

void CreateProjectMenu::RenderUI()
{
    glm::ivec2 windowSize;
    glfwGetWindowSize(mWnd, &windowSize.x, &windowSize.y);

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { (float)windowSize.x, (float)windowSize.y });
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 32.0f, 24.0f });
    ImGui::SetNextWindowPos({ 0.0f, 0.0f });

    ImGui::Begin("Create Project", nullptr, windowFlags);
    ImGui::PopStyleVar(3);

        ImGui::PushItemWidth((float)windowSize.x - 160); 
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 16.0f });

        // CREATE PROJECT
        ImGui::Text("CREATE PROJECT");
        ImGui::InputText("Project Name", &projectName);
        ImGui::InputText("Project Path", &createProjectPath);

        ImGui::PopStyleVar();
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 64.0f });
        if (ImGui::Button("CREATE", { windowSize.x - 64.0f, 24.0f }))
        {
            // TODO: Create project
        }
        ImGui::PopStyleVar();
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 16.0f });

        
        // OPEN EXISTING PROJECT
        ImGui::Text("OPEN EXISTING PROJECT");
        if (ImGui::Button("LOAD", { windowSize.x - 64.0f, 24.0f }))
        {
            // TODO: Load project
        }
        
        ImGui::PopItemWidth();
        ImGui::PopStyleVar();
    
    ImGui::End();
}

void CreateProjectMenu::ProcessInputs()
{

}

void CreateProjectMenu::Dispose()
{
    
}
