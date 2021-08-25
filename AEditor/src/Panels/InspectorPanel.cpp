#include "InspectorPanel.hpp"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <typeinfo>

void InspectorPanel::Render()
{
    Entity* current = *currentEntityPPtr;

    ImGui::Begin("Inspector");
    if (current != nullptr)
    {
        // TODO: Read component properties

        Transform* transform = current->GetComponent<Transform>();
        SpriteRenderer* spriteRenderer = current->GetComponent<SpriteRenderer>();

        ImGui::Text("Transform");
        ImGui::DragFloat3("Position", glm::value_ptr(transform->Position), 0.01f);
        ImGui::DragFloat3("Scale", glm::value_ptr(transform->Scale), 0.01f);
        ImGui::DragFloat("Rotation", &transform->Rotation, 0.5f);

        ImGui::NewLine();
        ImGui::Text("Sprite Renderer");
        ImGui::ColorEdit4("Color", glm::value_ptr(spriteRenderer->Color));
    }
    ImGui::End();
}
