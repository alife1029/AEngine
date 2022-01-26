#pragma once

#include <AE_API.hpp>
#include <string>
#include <map>
#include <cstdint>
#include <glm/vec2.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

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
        
    };

    class AE_API FontManager
    {
    public:
        void Initialize();
        void Shutdown();
        FontFamily* LoadFont(const std::string& fontFile);
    private:
        std::map<std::string, FontFamily*> m_Fonts;
        FT_Library m_Ft;
    };
}
