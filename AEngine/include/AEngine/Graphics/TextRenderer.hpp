#pragma once 

#include <AE_API.hpp>
#include "FontManager.hpp"
#include "ShaderProgram.hpp"
#include "../Application/Window.hpp"
#include <glm/glm.hpp>
#include <string>

namespace aengine
{
    // TODO: Optimize this class
    class AE_API TextRenderer
    {
    friend class Application;
    public:
        static void RenderText(const FontFamily* font, const std::string& text, float x, float y, float scale, const glm::vec4& color);

    private:
        static void Initialize(Window* targetWindow);
        static void Shutdown();
    
    private:
        static Window* m_TargetWindow;
        static ShaderProgram* m_Shader;
        static uint32_t m_VAO;
        static uint32_t m_VBO;
        static uint32_t m_EBO;
    };
}
