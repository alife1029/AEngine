#include "CreateProjectMenu.hpp"
#include "EditorMenu.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <fstream>

using namespace aengine;

CreateProjectMenu::CreateProjectMenu(Application* app) : Menu(app) { }

void CreateProjectMenu::Start()
{
    mWnd = mApp->GetGLFWwindow();
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
            showLoadDialog = true;
        }
        
        ImGui::PopItemWidth();
        ImGui::PopStyleVar();
    
    ImGui::End();

    if (showLoadDialog)
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 1.0f });
        ImGui::Begin("Load Project", nullptr, ImGuiWindowFlags_NoDocking);
            if (ImGui::Button("Cancel")) showLoadDialog = false;
            if (ImGui::Button("Load")) loadProject = true;

            std::string loadProjectPath;

            #if defined(__linux__)
            loadProjectPath = "/home";
            #elif defined(_WIN32)
            // TODO: Set default path on windows
            laodProjectPath = "C:/";
            #endif

            nodeIndex = 0;
            for (const auto& entry : std::filesystem::directory_iterator(loadProjectPath))
                DrawNode(entry.path());

        ImGui::End();
        ImGui::PopStyleColor();
    }

    if (createProject) CreateProject();
    else if (loadProject) LoadProject();
}

void CreateProjectMenu::DrawNode(const std::filesystem::path& path)
{
    if (!std::filesystem::is_directory(path))
    {
        if (!CheckFileExtension(path, "aeproject"))
        {
            return;
        }
    }

    std::string displayPath = path;
    size_t lastSlashIndex;
    for (size_t i = displayPath.size() - 1; i >= 0; i--) {
        if (displayPath[i] == '/' || displayPath[i] == '\\') {
            lastSlashIndex = i;
            break;
        }
    }
    displayPath = displayPath.erase(0, lastSlashIndex + 1);

    if (displayPath[0] == '.')
        return;

    ImGuiTreeNodeFlags flags = ((selectedPath == path) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    bool opened = ImGui::TreeNodeEx((void*)nodeIndex, flags, displayPath.c_str(), "");
    if (ImGui::IsItemClicked()) selectedPath = path;

    ++nodeIndex;

    if (opened) 
    {
        for (const auto& entry : std::filesystem::directory_iterator(path))
            DrawNode(entry.path());

        ImGui::TreePop();
    }
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
    proj->mPath = projectRoot;
    proj->Save();

    // Set this project as current project
    project = &proj;

    LoadEditorMenu();
}

void CreateProjectMenu::LoadProject()
{
    if (!CheckFileExtension(selectedPath, "aeproject"))
        return;

    AEProject* proj = new AEProject(selectedPath);
    project = &proj;

    showLoadDialog = false;

    LoadEditorMenu();
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

bool CreateProjectMenu::CheckFileExtension(const std::string& path, const std::string& extension)
{
    auto const extensionPos = path.find_last_of('.');
    const auto ext = path.substr(extensionPos + 1);

    if (ext != extension) return false;
    return true;
}
