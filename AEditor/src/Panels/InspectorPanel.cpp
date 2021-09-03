#include "InspectorPanel.hpp"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

void InspectorPanel::Render()
{
    Entity* current = *currentEntityPPtr;

    ImGui::Begin("Inspector");
    if (current != nullptr)
    {
        current->OnInspector();
    }
    ImGui::End();
}
