#ifndef AE_TRANSFORM_COMPONENT_HPP
#define AE_TRANSFORM_COMPONENT_HPP

#include "AE_API.hpp"
#include "../Component.hpp"
#include <glm/mat4x4.hpp>

namespace aengine
{
    class AE_API Transform : public Component
    {
    public:
        glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale = { 1.0f, 1.0f, 0.0f };
        float Rotation = 0.0f;
    public:
        void Start() override;
        void Update() override;
        void OnInspector() override;
        void Serialize(YAML::Emitter& out) override;
        void Deserialize() override;

        // Getters
        operator glm::mat4() const noexcept;
        operator const glm::mat4&() const noexcept;
        const glm::mat4& TransformMatrix() const noexcept;

        GETTYPE_DEC();
    private:
        void CalculateMatrix() noexcept;
    private:
        glm::mat4 mTransformMatrix;
        bool mFirstFrame;
        bool mChanged;
        glm::vec3 mLastPos;
        glm::vec3 mLastScale;
        float mLastRotation;
    };
}

#endif
