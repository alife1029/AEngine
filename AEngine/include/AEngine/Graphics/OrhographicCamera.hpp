#ifndef ORTHOGRAPHIC_CAMERA_HPP
#define ORTHOGRAPHIC_CAMERA_HPP

#include "AE_API.hpp"
#include "Viewport.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace aengine
{
    class AE_API OrthographicCamera
    {
    public:
        OrthographicCamera(Viewport* viewport, float size);

        void Update() noexcept;

        void SetZoom(float amount) noexcept;
        void SetPosition(const glm::vec3& pos) noexcept;
        void SetPosition(const glm::vec2& pos) noexcept;
        void SetPosition(float x, float y, float z = 0.0f) noexcept;
        void SetRotation(float rot) noexcept;
        void Zoom(float amount) noexcept;
        void Translate(const glm::vec3& amount) noexcept;
        void Translate(const glm::vec2& amount) noexcept;
        void Translate(float x, float y, float z = 0.0f) noexcept;
        void Rotate(float amount) noexcept;

        float ZoomValue() const noexcept;
        float Rotation() const noexcept;
        const glm::vec3& Position() const noexcept;
        const glm::mat4& Combined() const noexcept;
        const glm::mat4& View() const noexcept;
        const glm::mat4& Proj() const noexcept;
    private:
        float mRotation;
        glm::vec3 mPosition;

        // Transform and projection matrices
        glm::mat4 mCombined;
        glm::mat4 mView;
        glm::mat4 mProj;

        float mSize;
        Viewport* mViewport;
    };
}

#endif
