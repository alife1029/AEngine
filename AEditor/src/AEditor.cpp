#include "AEditor.hpp"
#include "Menus/EditorMenu.hpp"
#include "Menus/CreateProjectMenu.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

AEditor::AEditor(const AppConfig& config) : Application(config) { }

void AEditor::Start()
{
    // Setup context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup platform & renderer
    ImGui_ImplGlfw_InitForOpenGL(GetGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330"); // Init for OpenGL 3.3

    // Color theme
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.FontDefault = io.Fonts->AddFontFromFileTTF("Fonts/Inter.ttf", 15.0f);
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    mActiveProject = nullptr;
    CreateProjectMenu* projectMenu = new CreateProjectMenu(this);
    projectMenu->project = &mActiveProject;
    projectMenu->mCurrentMenu = &mActiveMenu;
    mActiveMenu = projectMenu;

    mActiveMenu->Start();
}

void AEditor::Update()
{
    mActiveMenu->Update();
}

void AEditor::Dispose()
{
    mActiveMenu->Dispose();
    delete mActiveMenu;

    // Clear ImGui data
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
