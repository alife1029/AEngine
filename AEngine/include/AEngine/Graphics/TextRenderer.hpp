#pragma once 

#include <AE_API.hpp>
#include "FontManager.hpp"
#include "../Application/Window.hpp"
#include <glm/glm.hpp>
#include <string>

namespace aengine
{
    class AE_API TextRenderer
    {
    friend class Application;
    public:
        static void SetRenderingFont(const FontFamily* font);
        static void RenderText(const std::string& text, float x = 0.0f, float y = 0.0f, float fontSize = 1.0f, const glm::vec4& color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

    private:
        static void Initialize(Window* targetWindow);
        static void Shutdown();
        static void Begin();
        static void End();
    
    private:
        static Window* m_TargetWindow;
        static const FontFamily* m_Font;
    };
}
