#include "AEngine/Scene/Components/SpriteRenderer.hpp"
#include "AEngine/Scene/Entity.hpp"
#include "AEngine/Graphics/Renderer2D.hpp"

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

    GETTYPE_IMP(SpriteRenderer)
}
