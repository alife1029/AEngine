#include "AEngine/Scene/Components/SpriteRenderer.hpp"
#include "AEngine/Scene/Entity.hpp"
#include "AEngine/Graphics/Renderer2D.hpp"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace aengine
{
    void SpriteRenderer::Start()
    {
        mTransform = mEntity->GetComponent<Transform>();
    }

    void SpriteRenderer::Update()
    {
        Renderer2D::DrawQuad(   Texture != nullptr ? Texture : Texture2D::WhiteTex(), 
                                mTransform->TransformMatrix(), Color);
    }

    void SpriteRenderer::OnInspector()
    {
        ImGui::Text("Sprite Renderer");
        ImGui::ColorEdit4("Color", glm::value_ptr(Color));
    }

    void SpriteRenderer::Serialize(YAML::Emitter& out)
    {
        out << YAML::Key << "Color" << YAML::Value << YAML::BeginSeq
                << std::to_string(Color.r) << std::to_string(Color.g) << std::to_string(Color.b) << std::to_string(Color.a) << YAML::EndSeq;
    }

    GETTYPE_IMP(SpriteRenderer)
}
