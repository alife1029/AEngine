#ifndef AED_EDITOR_MENU_HPP
#define AED_EDITOR_MENU_HPP

#include "Menu.hpp"
#include <AEngine.hpp>
#include "../Panels/SceneHierachyPanel.hpp"
#include "../Panels/InspectorPanel.hpp"
#include "../Panels/AssetsPanel.hpp"
#include "../Core/Project.hpp"

using namespace aengine;

struct GLFWwindow;

class EditorMenu : public Menu
{
private:
    SceneHierarchyPanel mHierarchyPanel;
    InspectorPanel mInspectorPanel;
    AssetsPanel mAssetsPanel;

    OrthographicCamera* sceneCamera;
    Viewport* viewport;
    Scene* mScene;
    GLFWwindow* mWnd;
    Entity* selectedEntity;

    bool viewportFocused = false;
public:
    AEProject** project;
public:
    EditorMenu(Application* app);
    void Start();
    void Update();
    void Dispose();
private:
    void RenderUI();
    void RenderViewport();
    void ProcessInputs();
private:
    void CreateEntity();
    void SaveScene();
    void LoadScene();
};

#endif
