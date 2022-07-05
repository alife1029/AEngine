#include "CreateProjectMenu.hpp"
#include "EditorMenu.hpp"
#include "../Utils.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <dirent.h>
#include <filesystem>

using namespace aengine;

std::vector<Path> ReadDirectory(const std::string& path, bool skipErrors = true);

CreateProjectMenu::CreateProjectMenu(Application* app) : Menu(app) { }

void CreateProjectMenu::Start()
{
    mWnd = mApp->GetGLFWwindow();
    mApp->BindMainCamera(nullptr);
}

void CreateProjectMenu::Update()
{
    // Init UI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ProcessInputs();
    RenderUI();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void CreateProjectMenu::RenderUI()
{
    glm::ivec2 windowSize;
    glfwGetWindowSize(mWnd, &windowSize.x, &windowSize.y);

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
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
        ImGui::InputText("Project Path", &projectPath);

        ImGui::PopStyleVar();
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 64.0f });
        if (ImGui::Button("CREATE", { windowSize.x - 64.0f, 24.0f }))
        {
            createProject = true;
        }
        ImGui::PopStyleVar();
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 16.0f });

        
        // OPEN EXISTING PROJECT
        ImGui::Text("OPEN EXISTING PROJECT");
        if (ImGui::Button("LOAD", { windowSize.x - 64.0f, 24.0f }))
        {
            loadProject = true;
        }
        
        ImGui::PopItemWidth();
        ImGui::PopStyleVar();
    
    ImGui::End();

    if (createProject) CreateProject();
    else if (loadProject) LoadProject();
}

void CreateProjectMenu::CreateProject()
{
    std::string projectRoot = projectPath + "/" + projectName;

    // Create directories
    std::filesystem::create_directory(projectRoot);
    std::filesystem::create_directory(projectRoot + "/Assets");
    std::filesystem::create_directory(projectRoot + "/bin");
    std::filesystem::create_directory(projectRoot + "/obj");

    // Create project class
    AEProject* proj = new AEProject();
    proj->mProjectName = projectName;
    proj->mPath = projectRoot + "/" + projectName + ".aeproject";
    proj->Save();

    // Set this project as current project
    project = &proj;

    LoadEditorMenu();
}

void CreateProjectMenu::LoadProject()
{
    loadProject = false;
    
    std::string selectedPath = FileDialog::OpenFile(FileDialog::Filter("AEngine Project", { ".aeproject" }));
    Logger::LogToFile(selectedPath);
    if (!selectedPath.empty())
    {
        AEProject* proj = new AEProject(selectedPath);
        project = &proj;

        LoadEditorMenu();
    }
}

void CreateProjectMenu::LoadEditorMenu()
{
    EditorMenu* editorMenu = new EditorMenu(mApp);
    editorMenu->project = project;
    *mCurrentMenu = editorMenu;

    editorMenu->Start();

    glfwSetWindowSize(mApp->GetGLFWwindow(), 1024, 640);

    Dispose();
    delete this;
}

void CreateProjectMenu::ProcessInputs()
{
    if (Input::IsKeyJustPressed(Key::Enter))
        createProject = true;
}

void CreateProjectMenu::Dispose()
{
    
}

std::vector<Path> ReadDirectory(const std::string& path, bool skipErrors)
{
    std::vector<Path> ret;

    DIR* dir;
    struct dirent* diread;

    if ((dir = opendir(path.c_str())) != nullptr)
    {
        while ((diread = readdir(dir)) != nullptr)
        {
            std::string fileName = path + std::string(diread->d_name);
            if (diread->d_type == DT_DIR) fileName += "/";
            ret.push_back({ fileName, diread->d_type == DT_DIR });
        }
        closedir(dir);
    }
    else
    {
        if (!skipErrors)
        {
            std::ostringstream oss;
            oss << "Failed to read directories in " << path;
            ThrowAEexceptionWMSG(oss.str());
        }
    }

    return ret;
}
