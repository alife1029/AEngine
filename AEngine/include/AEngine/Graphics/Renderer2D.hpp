#pragma once

#include "AE_API.hpp"
#include "Texture2D.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <cstdint>

namespace aengine
{
    class AE_API RendererStat
    {
        friend class Renderer2D;
    public:
        RendererStat();
        uint32_t QuadCount() const noexcept;
        uint32_t VertexCount() const noexcept;
        uint32_t BatchCount() const noexcept;
    private:
        uint32_t mDrawCalls;
        uint32_t mQuadCount;
    };

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

        static const RendererStat& Stats();
    private:
        static void Init();
        static void Shutdown();
        static void ResetStats();
        static void Begin(const glm::mat4& viewProj);
        static void End();
        static void Flush();
    };
}
