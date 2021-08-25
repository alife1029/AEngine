#ifndef AED_CREATE_PROJECT_MENU_HPP
#define AED_CREATE_PROJECT_MENU_HPP

#include "Menu.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class CreateProjectMenu : public Menu
{
private:
    GLFWwindow* mWnd;
    std::string projectName;
    std::string projectPath;
    std::string createProjectPath;
public:
    CreateProjectMenu(aengine::Application* app);
    void Start();
    void Update();
    void Dispose();
private:
    void RenderUI();
    void ProcessInputs();
};

#endif
