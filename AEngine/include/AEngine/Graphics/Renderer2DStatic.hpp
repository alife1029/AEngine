#pragma once

#include "AE_API.hpp"
#include "Texture2D.hpp"
#include <glm/glm.hpp>

namespace aengine
{
    class AE_API Renderer2DStatic
    {
        friend class Application;
    public:
        static void Begin();
        static void End();
        static void Clear();

        static void AddQuad(const glm::mat4& transform);
        static void AddQuad(const glm::mat4& transform, const glm::vec4& color);
        static void AddQuad(const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec4& color);
        static void AddQuad(const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color);
        static void AddQuad(const glm::vec3& pos, const glm::vec3& scale, float rotation);
        static void AddQuad(const glm::vec3& pos, const glm::vec3& scale);
        static void AddQuad(const glm::vec3& pos, float rotation, const glm::vec4& color);
        static void AddQuad(const glm::vec3& pos, float rotation);
        static void AddQuad(const glm::vec3& pos, const glm::vec4& color);
        static void AddQuad(const glm::vec3& pos);

        static void AddQuad(const Texture2D* tex, const glm::mat4& transform);
        static void AddQuad(const Texture2D* tex, const glm::mat4& transform, const glm::vec4& color);
        static void AddQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec4& color);
        static void AddQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color);
        static void AddQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, float rotation);
        static void AddQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale);
        static void AddQuad(const Texture2D* tex, const glm::vec3& pos, float rotation, const glm::vec4& color);
        static void AddQuad(const Texture2D* tex, const glm::vec3& pos, float rotation);
        static void AddQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec4& color);
        static void AddQuad(const Texture2D* tex, const glm::vec3& pos);

    private:
        static void Init();
        static void Shutdown();
        static void RenderScene(const glm::mat4& viewProj);
    };
}
