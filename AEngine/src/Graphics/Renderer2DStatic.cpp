#include "AEngine/Graphics/Renderer2DStatic.hpp"
#include "AEngine/Graphics/ShaderProgram.hpp"
#include "AEngine/Graphics/Vertex.hpp"
#include "AEngine/Graphics/RendererStat.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <vector>

#define DEFAULT_SCALE glm::vec3(1.0f, 1.0f, 0.0f)
#define DEFAULT_ROTATION 0.0f
#define DEFAULT_COLOR glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
#define DEFAULT_TEXTURE Texture2D::WhiteTex()

namespace aengine
{
    static constexpr uint32_t MaxQuads = 1000;
    static constexpr uint32_t MaxVertices = MaxQuads * 4;
    static constexpr uint32_t MaxIndices = MaxQuads * 6;
    static constexpr uint32_t MaxTextures = 32;

    struct Batch
    {
        uint32_t VAO, VBO;
        uint32_t IndexCount;

        std::array<uint32_t, MaxTextures> TextureSlots;
        uint32_t TextureSlotIndex;

        void Dispose()
        {
            if (VAO) glDeleteVertexArrays(1, &VAO);
            if (VBO) glDeleteBuffers(1, &VBO);
        }
    };

    struct RendererData
    {
        uint32_t EBO;

        ShaderProgram* Shader;
        std::vector<Batch> Batches;
        
        Vertex2D* Buffer;
        Vertex2D* BufferPtr;

        std::array<uint32_t, MaxTextures> TextureSlots;
        uint32_t TextureSlotIndex = 1;

        uint32_t IndexCount = 0;

        bool SceneRegistered = false;
    };

    static RendererData rendererData;

    void Renderer2DStatic::Init()
    {
        rendererData.Shader = new ShaderProgram("glsl/default_v.glsl", "glsl/default_f.glsl");

        // Calculate indices
        uint32_t indices[MaxIndices];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < MaxIndices; i += 6)
        {
            indices[i]      = offset;
            indices[i + 1]  = offset + 1;
            indices[i + 2]  = offset + 2;
            indices[i + 3]  = offset;
            indices[i + 4]  = offset + 2;
            indices[i + 5]  = offset + 3;
            offset += 4;
        }

        // Generate EBO
        glGenBuffers(1, &rendererData.EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererData.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // Initialize texture slots
        rendererData.TextureSlots[0] = Texture2D::WhiteTex()->ID();
        for (size_t i = 1; i < MaxTextures; i++)
            rendererData.TextureSlots[i] = 0;

        // Vertex buffer
        rendererData.Buffer = new Vertex2D[MaxVertices];
        rendererData.BufferPtr = rendererData.Buffer;

        rendererData.SceneRegistered = false;
    }

    void Renderer2DStatic::Shutdown()
    {
        Clear();

        glDeleteBuffers(1, &rendererData.EBO);

        delete[] rendererData.Buffer;
        delete rendererData.Shader;

        rendererData.SceneRegistered = false;
    }

    void Renderer2DStatic::Begin()
    {
        rendererData.BufferPtr = rendererData.Buffer;
        rendererData.SceneRegistered = false;
        rendererData.TextureSlotIndex = 1;
        rendererData.IndexCount = 0;
    }

    void Renderer2DStatic::End()
    {
        Batch batch;
        batch.IndexCount = rendererData.IndexCount;

        GLsizeiptr vertexSize = (uint8_t*)rendererData.BufferPtr - (uint8_t*)rendererData.Buffer;

        // Load vertex datas
        glGenVertexArrays(1, &batch.VAO);
        glGenBuffers(1, &batch.VBO);
        glBindVertexArray(batch.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexSize, rendererData.Buffer, GL_STATIC_DRAW);

        // Vertex attributes
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, Position));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, Color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, TexCoord));
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void*)offsetof(Vertex2D, TexIndex));

        batch.TextureSlots = rendererData.TextureSlots;
        batch.TextureSlotIndex = rendererData.TextureSlotIndex;
        batch.IndexCount = rendererData.IndexCount;

        rendererData.Batches.push_back(batch);
        rendererData.SceneRegistered = true;

        ++RendererStat::mStaticQuadBatches;
    }

    void Renderer2DStatic::Clear()
    {
        // Delete all batches
        for (auto batch : rendererData.Batches)
            batch.Dispose();
        rendererData.Batches.clear();

        rendererData.SceneRegistered = false;

        RendererStat::mStaticQuadBatches = 0;
        RendererStat::mStaticQuadCount = 0;
    }

    void Renderer2DStatic::RenderScene(const glm::mat4& viewProj)
    {
        if (rendererData.SceneRegistered)
        {
            rendererData.Shader->Use();
            
            // Render all batches
            for (auto batch : rendererData.Batches)
            {
                // Activate texture units
                int* samplers = (int*)malloc(batch.TextureSlotIndex * sizeof(int));
                for (uint32_t i = 0; i < batch.TextureSlotIndex; i++)
                {
                    samplers[i] = i;
                    glActiveTexture(GL_TEXTURE0 + i);
                    glBindTexture(GL_TEXTURE_2D, batch.TextureSlots[i]);
                }

                rendererData.Shader->SetIntArr("uSamplers", batch.TextureSlotIndex, samplers);
                rendererData.Shader->SetMat4("uViewProj", viewProj);

                glBindVertexArray(batch.VAO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererData.EBO);
                glDrawElements(GL_TRIANGLES, batch.IndexCount, GL_UNSIGNED_INT, nullptr);
                glBindVertexArray(0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

                free(samplers);
            }
        }
    }

    void Renderer2DStatic::AddQuad(const glm::mat4& transform)
    {
        AddQuad(DEFAULT_TEXTURE, transform, DEFAULT_COLOR);
    }
    void Renderer2DStatic::AddQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        AddQuad(DEFAULT_TEXTURE, transform, color);
    }
    void Renderer2DStatic::AddQuad(const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec4& color)
    {
        AddQuad(DEFAULT_TEXTURE, pos, scale, rotation, color);
    }
    void Renderer2DStatic::AddQuad(const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color)
    {
        AddQuad(DEFAULT_TEXTURE, pos, scale, DEFAULT_ROTATION, color);
    }
    void Renderer2DStatic::AddQuad(const glm::vec3& pos, const glm::vec3& scale, float rotation)
    {
        AddQuad(DEFAULT_TEXTURE, pos, scale, rotation, DEFAULT_COLOR);
    }
    void Renderer2DStatic::AddQuad(const glm::vec3& pos, const glm::vec3& scale)
    {
        AddQuad(DEFAULT_TEXTURE, pos, scale, DEFAULT_ROTATION, DEFAULT_COLOR);
    }
    void Renderer2DStatic::AddQuad(const glm::vec3& pos, float rotation, const glm::vec4& color)
    {
        AddQuad(DEFAULT_TEXTURE, pos, DEFAULT_SCALE, rotation, color);
    }
    void Renderer2DStatic::AddQuad(const glm::vec3& pos, float rotation)
    {
        AddQuad(DEFAULT_TEXTURE, pos, DEFAULT_SCALE, rotation, DEFAULT_COLOR);
    }
    void Renderer2DStatic::AddQuad(const glm::vec3& pos, const glm::vec4& color)
    {
        AddQuad(DEFAULT_TEXTURE, pos, DEFAULT_SCALE, DEFAULT_ROTATION, color);
    }
    void Renderer2DStatic::AddQuad(const glm::vec3& pos)
    {
        AddQuad(DEFAULT_TEXTURE, pos, DEFAULT_SCALE, DEFAULT_ROTATION, DEFAULT_COLOR);
    }
    void Renderer2DStatic::AddQuad(const Texture2D* tex, const glm::mat4& transform)
    {
        AddQuad(tex, transform, DEFAULT_COLOR);
    }
    void Renderer2DStatic::AddQuad(const Texture2D* tex, const glm::mat4& transform, const glm::vec4& color)
    {
        if (rendererData.IndexCount >= MaxIndices)
        {
            End();
            Begin();
        }

        // Find texrture layer
        float textureIndex = -1.0f;
        for (uint32_t i = 0; i < rendererData.TextureSlotIndex; i++)
        {
            if (rendererData.TextureSlots[i] == tex->ID())
            {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        // Create new texture layer
        if (textureIndex == -1.0f)
        {
            if (rendererData.TextureSlotIndex >= MaxTextures - 1)
            {
                End();
                Begin();
            }

            textureIndex = static_cast<float>(rendererData.TextureSlotIndex);
            rendererData.TextureSlots[rendererData.TextureSlotIndex] = tex->ID();
            ++rendererData.TextureSlotIndex;
        }

        // Vertex datas
        glm::vec4 vertexPoses[] = {
            { -0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f,  0.5f, 0.0f, 1.0f },
            { -0.5f,  0.5f, 0.0f, 1.0f }
        };
        glm::vec2 texCoords[] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f }
        };

        // Add vertices to buffer
        for (size_t i = 0; i < 4; i++)
        {
            rendererData.BufferPtr->Position = transform * vertexPoses[i];
            rendererData.BufferPtr->Color = color;
            rendererData.BufferPtr->TexCoord = texCoords[i];
            rendererData.BufferPtr->TexIndex = textureIndex;
            ++rendererData.BufferPtr;
        }

        rendererData.IndexCount += 6;
        ++RendererStat::mStaticQuadCount;
    }
    void Renderer2DStatic::AddQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec4& color)
    {
        AddQuad(tex, glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), pos), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }), scale), color);
    }
    void Renderer2DStatic::AddQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color)
    {
        AddQuad(tex, pos, scale, DEFAULT_ROTATION, color);
    }
    void Renderer2DStatic::AddQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale, float rotation)
    {
        AddQuad(tex, pos, scale, rotation, DEFAULT_COLOR);
    }
    void Renderer2DStatic::AddQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec3& scale)
    {
        AddQuad(tex, pos, scale, DEFAULT_ROTATION, DEFAULT_COLOR);
    }
    void Renderer2DStatic::AddQuad(const Texture2D* tex, const glm::vec3& pos, float rotation, const glm::vec4& color)
    {
        AddQuad(tex, pos, DEFAULT_SCALE, rotation, color);
    }
    void Renderer2DStatic::AddQuad(const Texture2D* tex, const glm::vec3& pos, float rotation)
    {
        AddQuad(tex, pos, DEFAULT_SCALE, rotation, DEFAULT_COLOR);
    }
    void Renderer2DStatic::AddQuad(const Texture2D* tex, const glm::vec3& pos, const glm::vec4& color)
    {
        AddQuad(tex, pos, DEFAULT_SCALE, DEFAULT_ROTATION, color);
    }
    void Renderer2DStatic::AddQuad(const Texture2D* tex, const glm::vec3& pos)
    {
        AddQuad(tex, pos, DEFAULT_SCALE, DEFAULT_ROTATION, DEFAULT_COLOR);
    }
}
