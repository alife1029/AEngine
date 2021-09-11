#include "AEngine/Scene/Components/Transform.hpp"
#include "AEngine/Utils/Logger.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace aengine
{
    void Transform::Start()
    {
        mFirstFrame = true;
        mChanged = true;
        CalculateMatrix();
    }

    void Transform::Update()
    {
        // Check transform values has changed
        if (!mChanged)
        {
            if (mLastPos != Position) mChanged = true;
            else if (mLastScale != Scale) mChanged = true;
            else if (mLastRotation != Rotation) mChanged = true;
        }

        // Recalculate transform matrix only if transform values changed
        if (mChanged) CalculateMatrix();
    }

    void Transform::OnInspector()
    {
        ImGui::Text("Transform");
        ImGui::DragFloat3("Position", glm::value_ptr(Position), 0.01f);
        ImGui::DragFloat3("Scale", glm::value_ptr(Scale), 0.01f);
        ImGui::DragFloat("Rotation", &Rotation, 0.5f);
    }

    void Transform::Serialize(YAML::Emitter& out)
    {
        double pos = Position.x;
        Logger::LogToFile(std::to_string(pos));
        out << YAML::Key << "Position" << YAML::Value << YAML::BeginSeq
                << std::to_string(Position.x) << std::to_string(Position.y) << std::to_string(Position.z) << YAML::EndSeq
            << YAML::Key << "Scale" << YAML::Value << YAML::BeginSeq
                << std::to_string(Scale.x) << std::to_string(Scale.y) << std::to_string(Scale.z) << YAML::EndSeq
            << YAML::Key << "Rotation" << YAML::Value << std::to_string(Rotation);
    }

    void Transform::CalculateMatrix() noexcept
    {
        // Calculate transform matrix
        const glm::mat4 identity = glm::mat4(1.0f);
        mTransformMatrix =    glm::translate(identity, Position) 
                            * glm::rotate(identity, glm::radians(Rotation), { 0.0f, 0.0f, 1.0f })
                            * glm::scale(identity, Scale);

        // Save last positions
        mLastPos = Position;
        mLastScale = Scale;
        mLastRotation = Rotation;

        mChanged = false;
    }

    Transform::operator glm::mat4() const noexcept { return mTransformMatrix; }
    Transform::operator const glm::mat4&() const noexcept { return mTransformMatrix; }
    const glm::mat4& Transform::TransformMatrix() const noexcept { return mTransformMatrix; }

    GETTYPE_IMP(Transform)
}
