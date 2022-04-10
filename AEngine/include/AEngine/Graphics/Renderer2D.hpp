#pragma once

#include "AE_API.hpp"
#include "Texture2D.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <cstdint>

namespace aengine
{
    class AE_API Renderer2D
    {
        friend class Application;
    public:
        static void DrawQuad(const glm::mat4& transform);
        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos, const glm::vec3& scale, float rotation);
        static void DrawQuad(const glm::vec3& pos, const glm::vec3& scale);
        static void DrawQuad(const glm::vec3& pos, float rotation, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos, float rotation);
        static void DrawQuad(const glm::vec3& pos, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos);

        static void DrawQuad(const Texture2D* tex, const glm::mat4& transform);
        static void DrawQuad(const Texture2D* tex, const glm::mat4& transform, const glm::vec4& color);
        static void DrawQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec4& color);
        static void DrawQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color);
        static void DrawQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, float rotation);
        static void DrawQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale);
        static void DrawQuad(const Texture2D* tex, const glm::vec3& pos, float rotation, const glm::vec4& color);
        static void DrawQuad(const Texture2D* tex, const glm::vec3& pos, float rotation);
        static void DrawQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec4& color);
        static void DrawQuad(const Texture2D* tex, const glm::vec3& pos);
    private:
        static void Init();
        static void Shutdown();
        static void Begin(const glm::mat4& viewProj);
        static void End();
        static void Flush();
    };
}
