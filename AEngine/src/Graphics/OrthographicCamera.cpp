#include "AEngine/Graphics/OrhographicCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace aengine
{
    OrthographicCamera::OrthographicCamera(Viewport* viewport, float size)
        : mViewport(viewport), mSize(size), mRotation(0.0f), mPosition({ 0.0f, 0.0f, 0.0f })
    {
        Update();
    }

    void OrthographicCamera::Update() noexcept
    {
        float w = mSize * mViewport->Aspect();

        mView = glm::rotate(glm::mat4(1.0f), -glm::radians(mRotation), { 0.0f, 0.0f, 1.0f })
            *   glm::translate(glm::mat4(1.0f), { -mPosition.x, -mPosition.y, -mPosition.z });
        mProj = glm::ortho(-w / 2.0f, w / 2.0f, -mSize / 2.0f, mSize / 2.0f);
        mCombined = mProj * mView;
    }

    // Transformation methods
    void OrthographicCamera::SetPosition(const glm::vec3& pos) noexcept
    {
        mPosition = pos;
    }
    void OrthographicCamera::SetPosition(const glm::vec2& pos) noexcept
    {
        mPosition.x = pos.x;
        mPosition.y = pos.y;
    }
    void OrthographicCamera::SetPosition(float x, float y, float z) noexcept
    {
        mPosition = { x, y , z };
    }
    void OrthographicCamera::SetRotation(float rot) noexcept
    {
        mRotation = rot;
    }
    void OrthographicCamera::Translate(const glm::vec3& amount) noexcept
    {
        mPosition += amount;
    }
    void OrthographicCamera::Translate(const glm::vec2& amount) noexcept
    {
        mPosition.x += amount.x;
        mPosition.y += amount.y;
    }
    void OrthographicCamera::Translate(float x, float y, float z) noexcept
    {
        mPosition.x += x;
        mPosition.y += y;
    }
    void OrthographicCamera::Rotate(float amount) noexcept
    {
        mRotation += amount;
    }

    // Getter methods
    float OrthographicCamera::Rotation() const noexcept
    {
        return mRotation;
    }
    const glm::vec3& OrthographicCamera::Position() const noexcept
    {
        return mPosition;
    }
    const glm::mat4& OrthographicCamera::Combined() const noexcept
    {
        return mCombined;
    }
    const glm::mat4& OrthographicCamera::View() const noexcept
    {
        return mView;
    }
    const glm::mat4& OrthographicCamera::Proj() const noexcept
    {
        return mProj;
    }
}
