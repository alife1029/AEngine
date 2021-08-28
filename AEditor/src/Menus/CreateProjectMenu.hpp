#ifndef AED_CREATE_PROJECT_MENU_HPP
#define AED_CREATE_PROJECT_MENU_HPP

#include "Menu.hpp"
#include "../Core/Project.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <filesystem>

class CreateProjectMenu : public Menu
{
private:
    GLFWwindow* mWnd;
    std::string projectName;
    std::string projectPath;
    
    bool showLoadDialog = false;
    std::filesystem::path selectedPath;
    size_t nodeIndex;

    bool createProject = false;
    bool loadProject = false;
public:
    Menu** mCurrentMenu;
    AEProject** project;
public:
    CreateProjectMenu(aengine::Application* app);
    void Start();
    void Update();
    void Dispose();
private:
    void DrawNode(const std::filesystem::path& path);
    void RenderUI();
    void ProcessInputs();
    void CreateProject();
    void LoadProject();
    void LoadEditorMenu();
    bool CheckFileExtension(const std::string& path, const std::string& extension);
};

#endif
