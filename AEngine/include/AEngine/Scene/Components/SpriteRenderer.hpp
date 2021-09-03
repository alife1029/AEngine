#ifndef AE_SPRITE_RENDERER_COMPONENT_HPP
#define AE_SPRITE_RENDERER_COMPONENT_HPP

#include "AE_API.hpp"
#include "AEngine/Graphics/Texture2D.hpp"
#include "../Component.hpp"
#include "Transform.hpp"
#include <glm/glm.hpp>

namespace aengine
{
    class AE_API SpriteRenderer : public Component
    {
    public:
        glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
        Texture2D* Texture = nullptr;
    public:
        void Start() override;
        void Update() override;
        void OnInspector() override;
        void Serialize(YAML::Emitter& out) override;
        void Deserialize() override;

        GETTYPE_DEC();
    private:
        Transform* mTransform;
    };
}

#endif
