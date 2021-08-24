#include "SceneHierachyPanel.hpp"
#include <imgui.h>

void SceneHierarchyPanel::Start()
{
    mSelectionContext = nullptr;
}

void SceneHierarchyPanel::Render()
{
    ImGui::Begin("Hierarchy");

    size_t entityCount = scene->Entities().size();
    for (size_t i = 0; i < entityCount; i++)
        DrawNode(i);

    ImGui::End();
}

void SceneHierarchyPanel::DrawNode(size_t entityIndex)
{
    Entity* entity = scene->Entities()[entityIndex];

    ImGuiTreeNodeFlags flags = ((mSelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    bool opened = ImGui::TreeNodeEx((void*)(size_t)entity->ID(), flags, entity->Tag().c_str());
    if (ImGui::IsItemClicked()) mSelectionContext = entity;

    bool entityDeleted = false;
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Delete Entity")) entityDeleted = true;
        ImGui::EndPopup();
    }

    if (opened) ImGui::TreePop();

    if (entityDeleted)
    {
        // TODO: Delete entity
    }
}
