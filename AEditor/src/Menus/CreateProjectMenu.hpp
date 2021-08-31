#ifndef AED_CREATE_PROJECT_MENU_HPP
#define AED_CREATE_PROJECT_MENU_HPP

#include "Menu.hpp"
#include "../Core/Project.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

struct Path
{
    std::string path;
    bool isDirectory;
};

class CreateProjectMenu : public Menu
{
private:
    GLFWwindow* mWnd;
    std::string projectName;
    std::string projectPath;
    
    std::string selectedPath;
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
    void RenderUI();
    void ProcessInputs();
    void CreateProject();
    void LoadProject();
    void LoadEditorMenu();
};

#endif
