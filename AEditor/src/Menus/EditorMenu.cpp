#include "EditorMenu.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

EditorMenu::EditorMenu(Application* app) : Menu(app) { }

void EditorMenu::Start()
{
    mWnd = mApp->GetGLFWwindow();
    viewport = new Viewport(0, 0);
    sceneCamera = new OrthographicCamera(viewport, 5.0f);

    mScene = new Scene();
    mScene->StartRenderers();

    mHierarchyPanel.scene = mScene;
    mInspectorPanel.currentEntityPPtr = &mHierarchyPanel.mSelectionContext;

    mHierarchyPanel.Start();
    mInspectorPanel.Start();
}

void EditorMenu::Update()
{
    ImGuiIO& io = ImGui::GetIO();
    glm::ivec2 windowSize;
    glfwGetWindowSize(mWnd, &windowSize.x, &windowSize.y);
    io.DisplaySize = ImVec2(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
    io.DeltaTime = Time::DeltaTimeF();

    // Init UI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    RenderUI();

    // Render form
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
    }

    ProcessInputs();
    printf("Editor menu updated!\n");
}

void EditorMenu::RenderUI()
{
    static bool dockspaceOpen = true;
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    float minWinSizeX = style.WindowMinSize.x;
    style.WindowMinSize.x = 370.0f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    style.WindowMinSize.x = minWinSizeX;

    if (ImGui::BeginMenuBar())
    {
        // File Menu
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N")) printf("New\n");
            if (ImGui::MenuItem("Open", "Ctrl+O")) printf("Open\n");
            if (ImGui::MenuItem("Save", "Ctrl+S")) printf("Save\n");
            if (ImGui::MenuItem("Save As", "Ctrl+Shift+S")) printf("Save As\n");
            if (ImGui::MenuItem("Exit")) printf("Exit\n");

            ImGui::EndMenu();
        }

        // Entity Menu
        if (ImGui::BeginMenu("Create"))
        {
            if (ImGui::MenuItem("Sprite"))
            {
                CreateEntity();
            }
            if (ImGui::MenuItem("Camera")) printf("Camera Created!\n");

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Scene panel
    mHierarchyPanel.Render();

    // Inspector panel
    mInspectorPanel.Render();

    // Assets panel
    ImGui::Begin("Assets");
    ImGui::Text("TODO: Assets Panel!\n");
    ImGui::End();

    // Viewport
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6, 6));
    
    ImGui::Begin("Viewport");
        glm::ivec2 windowSize;
        glm::ivec2 viewportPos, viewportSize;

        glfwGetWindowSize(mWnd, &windowSize.x, &windowSize.y);

        // Calculate viewport pos
        viewportPos = {
            ImGui::GetWindowPos().x,
            windowSize.y - ImGui::GetWindowPos().y - ImGui::GetWindowHeight()
        };

        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();
        vMin.x += ImGui::GetWindowPos().x;
        vMin.y += ImGui::GetWindowPos().y;
        vMax.x += ImGui::GetWindowPos().x;
        vMax.y += ImGui::GetWindowPos().y;
        viewportSize = { (int)vMax.x - (int)vMin.x + 12, (int)vMax.y - (int)vMin.y + 12 };
        viewport->Update(viewportPos.x, viewportPos.y, viewportSize.x, viewportSize.y);
        RenderViewport();

        const RendererStat& stats = Renderer2D::Stats();
        ImGui::Text("Batches: %d", stats.BatchCount());
        ImGui::Text("Verts: %d", stats.VertexCount());
        ImGui::Text("Quads: %d", stats.QuadCount());
        ImGui::Text("Tris: %d", stats.QuadCount() * 2);
    ImGui::End();
    ImGui::PopStyleVar();

    ImGui::End();
}

void EditorMenu::RenderViewport()
{
    sceneCamera->Update();
    Renderer2D::Begin(sceneCamera->Combined());
    
    mScene->UpdateRenderers();

    Renderer2D::End();
    Renderer2D::Flush();
}

void EditorMenu::ProcessInputs()
{
    // Menu shortcuts
    bool shiftPressing = Input::IsKeyPressing(Key::LeftShift) || Input::IsKeyPressing(Key::RightShift);
    bool ctrlPressing = Input::IsKeyPressing(Key::LeftControl) || Input::IsKeyPressing(Key::RightControl);
    if (ctrlPressing)
    {
        if (Input::IsKeyJustPressed(Key::N)) printf("New\n");
        else if (Input::IsKeyJustPressed(Key::O)) printf("Open\n");
        else if (Input::IsKeyJustPressed(Key::S) && !shiftPressing) printf("Save\n");
        else if (Input::IsKeyJustPressed(Key::S) && shiftPressing) printf("Save As\n");
    }
}

void EditorMenu::Dispose()
{
    mHierarchyPanel.Dispose();
    mInspectorPanel.Dispose();

    mScene->Dispose();

    delete sceneCamera;
    delete viewport;
    delete mScene;
}

void EditorMenu::CreateEntity()
{
    Entity* newEntity = mScene->CreateEntity();
    SpriteRenderer* renderer = new SpriteRenderer();
    newEntity->AddComponent(renderer);
    newEntity->Start();
}
