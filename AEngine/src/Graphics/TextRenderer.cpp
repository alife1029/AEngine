#include "AEngine/Graphics/TextRenderer.hpp"
#include "AEngine/Graphics/FontManager.hpp"
#include "AEngine/Graphics/Vertex.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace aengine
{
    Window* TextRenderer::m_TargetWindow = nullptr;
    ShaderProgram* TextRenderer::m_Shader = nullptr;
    uint32_t TextRenderer::m_VAO = 0;
    uint32_t TextRenderer::m_VBO = 0;
    uint32_t TextRenderer::m_EBO = 0;

    void TextRenderer::Initialize(Window* targetWindow)
    {
        m_TargetWindow = targetWindow;
        m_Shader = new ShaderProgram("glsl/uitext_v.glsl", "glsl/uitext_f.glsl");

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexUIText) * 6, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexUIText), (const void*)offsetof(VertexUIText, Position));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexUIText), (const void*)offsetof(VertexUIText, TexCoord));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void TextRenderer::Shutdown()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);

        delete m_Shader;
    }

    void TextRenderer::RenderText(const FontFamily* font, const std::string& text, float x, float y, float scale, const glm::vec4& color)
    {
        m_Shader->Use();

        // Calculate view-proj matrix
        glm::mat4 viewProj = glm::ortho(0.0f, (float)m_TargetWindow->Width(), (float)m_TargetWindow->Height(), 0.0f);

        glUniformMatrix4fv(glGetUniformLocation(m_Shader->ID(), "u_ViewProjMatrix"), 1, GL_FALSE, glm::value_ptr(viewProj));
        glUniform4f(glGetUniformLocation(m_Shader->ID(), "u_TextColor"), color.r, color.g, color.b, color.a);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(m_VAO);

        // Iterate through all chars of text
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            FontFamily::Character ch = font->m_Chars[*c];

            glm::vec2 pos = { x + ch.Bearing.x * scale, y - (ch.Size.y /*- ch.Bearing.y*/) * scale};
            glm::vec2 dimension = { ch.Size.x * scale, ch.Size.y * scale };

            VertexUIText vertices[6] = {
                { { pos.x,                  pos.y + dimension.y },  { 0.0f, 1.0f } },
                { { pos.x,                  pos.y               },  { 0.0f, 0.0f } },
                { { pos.x + dimension.x,    pos.y               },  { 1.0f, 0.0f } },

                { { pos.x,                  pos.y + dimension.y },  { 0.0f, 1.0f } },
                { { pos.x + dimension.x,    pos.y               },  { 1.0f, 0.0f } },
                { { pos.x + dimension.x,    pos.y + dimension.y },  { 1.0f, 1.0f } }
            };

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            x += (ch.Advance >> 6) * scale;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
