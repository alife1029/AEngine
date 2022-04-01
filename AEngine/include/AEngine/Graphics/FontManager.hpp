#pragma once

#include <AE_API.hpp>
#include <string>
#include <map>
#include <cstdint>
#include <glm/vec2.hpp>

namespace aengine
{
    class AE_API FontFamily
    {
    friend class FontManager;
    friend class TextRenderer;
    public:

    private:
        struct Character
        {
            uint32_t    TextureID;
            glm::ivec2  Size;
            glm::ivec2  Bearing;
            uint32_t    Advance;
        };

        static std::map<char, Character> m_Chars;

        ~FontFamily();
        
    };

    class AE_API FontManager
    {
        friend class Application;
    public:
        static FontFamily* LoadFont(const std::string& fontFile);
    private:
        static void Dispose();
        static std::map<std::string, FontFamily*> m_Fonts;
    };
}
