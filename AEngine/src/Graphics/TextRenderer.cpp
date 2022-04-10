#include "AEngine/Graphics/TextRenderer.hpp"
#include "AEngine/Graphics/FontManager.hpp"
#include "AEngine/Graphics/ShaderProgram.hpp"
#include "AEngine/Graphics/Vertex.hpp"
#include "AEngine/Graphics/RendererStat.hpp"
#include "AEngine/Utils/Logger.hpp"
#include "AEngine/Exception/OpenGLException.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <vector>

namespace aengine
{
    Window* TextRenderer::m_TargetWindow = nullptr;
    const FontFamily* TextRenderer::m_Font = nullptr;
    
    struct RendererData
    {
        GLuint VAO = 0;
        GLuint VBO = 0;
        GLuint EBO = 0;

        uint32_t IndexCount = 0;

        VertexUIText* Buffer = nullptr;
        VertexUIText* BufferPtr = nullptr;

        std::array<uint32_t, 32> TextureSlots;
        uint32_t TextureSlotIndex = 0;

        ShaderProgram* Shader;
        glm::mat4 ViewProj;

        static constexpr size_t MaxTexture = 32;
        static constexpr size_t MaxQuad = 1000;
        static constexpr size_t MaxVertices = MaxQuad * 4;
        static constexpr size_t MaxIndices = MaxQuad * 6;
    };

    static RendererData rendererData;

    void TextRenderer::SetRenderingFont(const FontFamily* font)
    {
        m_Font = font;
    }

    void TextRenderer::Initialize(Window* targetWindow)
    {
        m_TargetWindow = targetWindow;
        rendererData.Shader = new ShaderProgram("glsl/uitext_v.glsl", "glsl/uitext_f.glsl");

        rendererData.Buffer = new VertexUIText[rendererData.MaxVertices];

        glGenVertexArrays(1, &rendererData.VAO);
        glGenBuffers(1, &rendererData.VBO);

        glBindVertexArray(rendererData.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, rendererData.VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexUIText) * rendererData.MaxVertices, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexUIText), (const void*)offsetof(VertexUIText, Position));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexUIText), (const void*)offsetof(VertexUIText, Color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexUIText), (const void*)offsetof(VertexUIText, TexCoord));
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(VertexUIText), (const void*)offsetof(VertexUIText, TexIndex));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Generate indices
        uint32_t indices[rendererData.MaxIndices];
        uint32_t offset = 0;
        for (size_t i = 0; i < rendererData.MaxIndices; i += 6)
        {
            indices[i]      = offset;
            indices[i + 1]  = 1 + offset;
            indices[i + 2]  = 2 + offset;

            indices[i + 3]  = offset;
            indices[i + 4]  = 2 + offset;
            indices[i + 5]  = 3 + offset;

            offset += 4;
        }

        glGenBuffers(1, &rendererData.EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererData.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void TextRenderer::Shutdown()
    {
        glDeleteVertexArrays(1, &rendererData.VAO);
        glDeleteBuffers(1, &rendererData.VBO);
        glDeleteBuffers(1, &rendererData.EBO);

        delete[] rendererData.Buffer;
        delete rendererData.Shader;
    }

    void TextRenderer::Begin()
    {
        rendererData.BufferPtr = rendererData.Buffer;
        rendererData.ViewProj = glm::ortho(0.0f, (float)m_TargetWindow->Width(), 0.0f, (float)m_TargetWindow->Height());
    }

    void TextRenderer::End()
    {
        // Load vertex datas to GPU
        GLsizeiptr size = (uint8_t*)rendererData.BufferPtr - (uint8_t*)rendererData.Buffer;
        glBindBuffer(GL_ARRAY_BUFFER, rendererData.VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, &rendererData.Buffer[0]);

        // Draw
        rendererData.Shader->Use();
        int* samplers = (int*)alloca(rendererData.TextureSlotIndex * sizeof(int));
        for (uint32_t i = 0; i < rendererData.TextureSlotIndex; i++)
        {
            samplers[i] = i;
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, rendererData.TextureSlots[i]);
        }

        glUniform1iv(glGetUniformLocation(rendererData.Shader->ID(), "u_Text"), rendererData.TextureSlotIndex, samplers);
        glUniformMatrix4fv(glGetUniformLocation(rendererData.Shader->ID(), "u_ViewProjMatrix"), 1, GL_FALSE, glm::value_ptr(rendererData.ViewProj));

        glBindVertexArray(rendererData.VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererData.EBO);
        glDrawElements(GL_TRIANGLES, rendererData.IndexCount, GL_UNSIGNED_INT, nullptr);

        // TODO: Update renderer stats
        rendererData.IndexCount = 0;
        rendererData.TextureSlotIndex = 0;
        ++RendererStat::mTextBatches;
    }

    void TextRenderer::RenderText(const std::string& text, float x, float y, float fontSize, const glm::vec4& color)
    {
        if (m_Font == nullptr)
        {
            // TODO: Set a default font (maybe arial)
            Logger::LogToFile("You must set a font before rendering a text!", "Logs.log", LogType::Error);
            return;
        }

        rendererData.Shader->Use();

        glUniformMatrix4fv(glGetUniformLocation(rendererData.Shader->ID(), "u_ViewProjMatrix"), 1, GL_FALSE, glm::value_ptr(rendererData.ViewProj));
        glUniform4f(glGetUniformLocation(rendererData.Shader->ID(), "u_TextColor"), color.r, color.g, color.b, color.a);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(rendererData.VAO);

        // Iterate through all chars of text
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            if (rendererData.IndexCount >= rendererData.MaxIndices)
            {
                End();
                Begin();
            }

            FontFamily::Character ch = m_Font->m_Chars[*c];

            glm::vec2 pos = { x + ch.Bearing.x * fontSize, y - (ch.Size.y - ch.Bearing.y) * fontSize};
            glm::vec2 dimension = { ch.Size.x * fontSize, ch.Size.y * fontSize };

            glm::vec2 positions[] = {
                { pos.x,                  pos.y + dimension.y },
                { pos.x,                  pos.y               },
                { pos.x + dimension.x,    pos.y               },
                { pos.x + dimension.x,    pos.y + dimension.y }
            };
            glm::vec2 texCoords[] = {
                { 0.0f, 0.0f },
                { 0.0f, 1.0f },
                { 1.0f, 1.0f },
                { 1.0f, 0.0f }
            };

            float textureIndex = -1.0f;
            for (uint32_t i = 0; i < rendererData.TextureSlotIndex; i++)
            {
                if (rendererData.TextureSlots[i] == ch.TextureID)
                {
                    textureIndex = (float)i;
                    break;
                }
            }

            if (textureIndex == -1.0f)
            {
                if (rendererData.TextureSlotIndex >= rendererData.MaxTexture - 1)
                {
                    End();
                    Begin();
                }

                textureIndex = (float)rendererData.TextureSlotIndex;
                rendererData.TextureSlots[rendererData.TextureSlotIndex] = ch.TextureID;
                ++rendererData.TextureSlotIndex;
            }

            for (int i = 0; i < 4; i++)
            {
                rendererData.BufferPtr->Position = positions[i];
                rendererData.BufferPtr->Color = color;
                rendererData.BufferPtr->TexCoord = texCoords[i];
                rendererData.BufferPtr->TexIndex = textureIndex;
                ++rendererData.BufferPtr;
            }

            rendererData.IndexCount += 6;
            x += (ch.Advance >> 6) * fontSize;

            ++RendererStat::mTextQuadCount;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
