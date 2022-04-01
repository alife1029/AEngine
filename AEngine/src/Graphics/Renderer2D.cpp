#include "AEngine/Graphics/Renderer2D.hpp"
#include "AEngine/Graphics/ShaderProgram.hpp"
#include "AEngine/Graphics/Vertex.hpp"

#include <array>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default values
#define DEFAULT_SCALE glm::vec3(1.0f, 1.0f, 0.0f)
#define DEFAULT_ROTATION 0.0f
#define DEFAULT_COLOR glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
#define DEFAULT_TEXTURE Texture2D::WhiteTex()

// Maximum values
#define MAX_QUADS 1000
#define MAX_VERTICES MAX_QUADS * 4
#define MAX_INDICES MAX_QUADS * 6
#define MAX_TEXTURES 32

namespace aengine
{
    RendererStat::RendererStat()
        : mDrawCalls(0), mQuadCount(0) { }

    uint32_t RendererStat::QuadCount() const noexcept
    {
        return mQuadCount;
    }
    uint32_t RendererStat::VertexCount() const noexcept
    {
        return mQuadCount * 4;
    }
    uint32_t RendererStat::BatchCount() const noexcept
    {
        return mDrawCalls;
    }

    struct RendererData
    {
        GLuint QuadVA = 0;
        GLuint QuadVB = 0;
        GLuint QuadIB = 0;

        uint32_t WhiteTexture = 0;
        uint32_t WhiteTextureSlot = 0;

        uint32_t IndexCount = 0;

        Vertex2D* QuadBuffer = nullptr;
        Vertex2D* QuadBufferPtr = nullptr;

        std::array<uint32_t, MAX_TEXTURES> TextureSlots;
        uint32_t TextureSlotIndex = 0;

        ShaderProgram* Shader;
        glm::mat4 ViewProj;
    };

    static RendererData rendererData;
    static RendererStat rendererStat;

    void Renderer2D::Init()
    {
        rendererData.Shader = new ShaderProgram("glsl/default_v.glsl", "glsl/default_f.glsl");
        rendererData.Shader->Use();

        rendererData.QuadBuffer = new Vertex2D[MAX_VERTICES];

        // Generate OpenGL buffers
        glGenVertexArrays(1, &rendererData.QuadVA);
        glGenBuffers(1, &rendererData.QuadVB);
        glGenBuffers(1, &rendererData.QuadIB);

        // Bind GL buffers
        glBindVertexArray(rendererData.QuadVA);
        glBindBuffer(GL_ARRAY_BUFFER, rendererData.QuadVB);
        glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(Vertex2D), nullptr, GL_DYNAMIC_DRAW);

        // Vertex attribs
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, Position));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, Color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, TexCoord));
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, TexIndex));

        // Calculate indices
        uint32_t indices[MAX_INDICES];
        uint32_t offset = 0;
        for (size_t i = 0; i < MAX_INDICES; i += 6)
        {
            indices[i] = offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = offset;
            indices[i + 4] = 2 + offset;
            indices[i + 5] = 3 + offset;

            offset += 4;
        }

        // Load index buffer data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererData.QuadIB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        rendererData.WhiteTexture = Texture2D::WhiteTex()->ID();
        rendererData.TextureSlots[0] = rendererData.WhiteTexture;
        for (size_t i = 1; i < MAX_TEXTURES; i++)
            rendererData.TextureSlots[i] = 0;
    }

    void Renderer2D::Shutdown()
    {
        glDeleteVertexArrays(1, &rendererData.QuadVA);
        glDeleteBuffers(1, &rendererData.QuadVB);
        glDeleteBuffers(1, &rendererData.QuadIB);

        delete[] rendererData.QuadBuffer;
        delete rendererData.Shader;
    }

    void Renderer2D::Begin(const glm::mat4& viewProj)
    {
        rendererData.QuadBufferPtr = rendererData.QuadBuffer;
        rendererData.ViewProj = viewProj;
    }

    void Renderer2D::End()
    {
        // Load vertex datas to VRAM
        GLsizeiptr size = (uint8_t*)rendererData.QuadBufferPtr - (uint8_t*)rendererData.QuadBuffer;
        glBindBuffer(GL_ARRAY_BUFFER, rendererData.QuadVB);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, rendererData.QuadBuffer);
    }

    void Renderer2D::Flush()
    {
        rendererData.Shader->Use();

        // Bind texture layers
        int* samplers = (int*)alloca(rendererData.TextureSlotIndex * sizeof(int));
        for (uint32_t i = 0; i < rendererData.TextureSlotIndex; i++)
        {
            samplers[i] = i;
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, rendererData.TextureSlots[i]);
        }

        glUniform1iv(glGetUniformLocation(rendererData.Shader->ID(), "uSamplers"), rendererData.TextureSlotIndex, samplers);
        glUniformMatrix4fv(glGetUniformLocation(rendererData.Shader->ID(), "uViewProj"), 1, GL_FALSE, glm::value_ptr(rendererData.ViewProj));

        glBindVertexArray(rendererData.QuadVA);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererData.QuadIB);
        glDrawElements(GL_TRIANGLES, rendererData.IndexCount, GL_UNSIGNED_INT, nullptr);

        ++rendererStat.mDrawCalls;
        rendererData.IndexCount = 0;
        rendererData.TextureSlotIndex = 1;
    }

    void Renderer2D::DrawQuad(const glm::mat4& transform)
    {
        DrawQuad(DEFAULT_TEXTURE, transform, DEFAULT_COLOR);
    }
    void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        DrawQuad(DEFAULT_TEXTURE, transform, color);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec4& color)
    {
        DrawQuad(DEFAULT_TEXTURE, pos, scale, rotation, color);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color)
    {
        DrawQuad(DEFAULT_TEXTURE, pos, scale, DEFAULT_ROTATION, color);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec3& scale, float rotation)
    {
        DrawQuad(DEFAULT_TEXTURE, pos, scale, rotation, DEFAULT_COLOR);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec3& scale)
    {
        DrawQuad(DEFAULT_TEXTURE, pos, scale, DEFAULT_ROTATION, DEFAULT_COLOR);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, float rotation, const glm::vec4& color)
    {
        DrawQuad(DEFAULT_TEXTURE, pos, DEFAULT_SCALE, rotation, color);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, float rotation)
    {
        DrawQuad(DEFAULT_TEXTURE, pos, DEFAULT_SCALE, rotation, DEFAULT_COLOR);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec4& color)
    {
        DrawQuad(DEFAULT_TEXTURE, pos, DEFAULT_SCALE, DEFAULT_ROTATION, color);
    }
    void Renderer2D::DrawQuad(const glm::vec3& pos)
    {
        DrawQuad(DEFAULT_TEXTURE, pos, DEFAULT_SCALE, DEFAULT_ROTATION, DEFAULT_COLOR);
    }


    void Renderer2D::DrawQuad(const Texture2D* tex, const glm::mat4& transform, const glm::vec4& color)
    {
        if (rendererData.IndexCount >= MAX_INDICES || rendererData.TextureSlotIndex >= MAX_TEXTURES - 1)
        {
            End();
            Flush();
            Begin(rendererData.ViewProj);
        }

        float textureIndex = -1.0f;
        for (uint32_t i = 0; i < rendererData.TextureSlotIndex; i++)
        {
            if (rendererData.TextureSlots[i] == tex->ID())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == -1.0f)
        {
            textureIndex = (float)rendererData.TextureSlotIndex;
            rendererData.TextureSlots[rendererData.TextureSlotIndex] = tex->ID();
            ++rendererData.TextureSlotIndex;
        }
        
        // Calculate vertex poses using texture scales
        float texWH, texHH;
        texWH = (tex->Width() / 2.0f) / tex->PixelPerUnit();
        texHH = (tex->Height() / 2.0f) / tex->PixelPerUnit();
        glm::vec4 vertexPoses[] = {
            { -texWH, -texHH, 0.0f, 1.0f },
            {  texWH, -texHH, 0.0f, 1.0f },
            {  texWH,  texHH, 0.0f, 1.0f },
            { -texWH,  texHH, 0.0f, 1.0f }
        };
        glm::vec2 texCoords[] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f }
        };

        for (int i = 0; i < 4; i++)
        {
            glm::vec3 transformed = transform * vertexPoses[i];
            rendererData.QuadBufferPtr->Position = transformed;
            rendererData.QuadBufferPtr->Color = color;
            rendererData.QuadBufferPtr->TexCoord = texCoords[i];
            rendererData.QuadBufferPtr->TexIndex = textureIndex;
            ++rendererData.QuadBufferPtr;
        }

        rendererData.IndexCount += 6;
        ++rendererStat.mQuadCount;
    }
    void Renderer2D::DrawQuad(const Texture2D* tex, const glm::mat4& transform)
    {
        DrawQuad(tex, transform, DEFAULT_COLOR);
    }
    void Renderer2D::DrawQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
                            * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
                            * glm::scale(glm::mat4(1.0f), scale);
        DrawQuad(tex, transform);
    }
    void Renderer2D::DrawQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color)
    {
        DrawQuad(tex, pos, scale, DEFAULT_ROTATION, color);
    }
    void Renderer2D::DrawQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, float rotation)
    {
        DrawQuad(tex, pos, scale, rotation, DEFAULT_COLOR);
    }
    void Renderer2D::DrawQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale)
    {
        DrawQuad(tex, pos, scale, DEFAULT_ROTATION, DEFAULT_COLOR);
    }
    void Renderer2D::DrawQuad(const Texture2D* tex, const glm::vec3& pos, float rotation, const glm::vec4& color)
    {
        DrawQuad(tex, pos, DEFAULT_SCALE, rotation, color);
    }
    void Renderer2D::DrawQuad(const Texture2D* tex, const glm::vec3& pos, float rotation)
    {
        DrawQuad(tex, pos, DEFAULT_SCALE, rotation, DEFAULT_COLOR);
    }
    void Renderer2D::DrawQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec4& color)
    {
        DrawQuad(tex, pos, DEFAULT_SCALE, DEFAULT_ROTATION, color);
    }
    void Renderer2D::DrawQuad(const Texture2D* tex, const glm::vec3& pos)
    {
        DrawQuad(tex, pos, DEFAULT_SCALE, DEFAULT_ROTATION, DEFAULT_COLOR);
    }

    void Renderer2D::ResetStats()
    {
        rendererStat.mDrawCalls = 0;
        rendererStat.mQuadCount = 0;
    }

    const RendererStat& Renderer2D::Stats()
    {
        return rendererStat;
    }
}
