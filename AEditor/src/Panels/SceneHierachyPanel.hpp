#ifndef AED_PANEL_SCENE_HIERARCHY_PANEL_HPP
#define AED_PANEL_SCENE_HIERARCHY_PANEL_HPP

#include "Panel.hpp"
#include <AEngine.hpp>
#include <string>
#include <vector>

using namespace aengine;

class SceneHierarchyPanel : public Panel
{
public:
    Scene* scene;
    Entity* mSelectionContext;
public:
    void Start();
    void Render();
private:
    void DrawNode(size_t entityIndex);
};

#endif
