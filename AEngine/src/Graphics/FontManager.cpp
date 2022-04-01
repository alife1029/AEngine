#include "AEngine/Graphics/FontManager.hpp"
#include "AEngine/Exception/InitializationException.hpp"
#include "AEngine/Utils/Logger.hpp"
#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace aengine
{
    std::map<char, FontFamily::Character> FontFamily::m_Chars = std::map<char, FontFamily::Character>();
    std::map<std::string, FontFamily*> FontManager::m_Fonts = std::map<std::string, FontFamily*>();

    void FontManager::Dispose()
    {
        // Delete loaded fonts
        for (auto& [key, val] : m_Fonts)
        {
            delete val;
        }
    }

    FontFamily* FontManager::LoadFont(const std::string& fontFile)
    {
        FT_Library m_Ft;

        if (FT_Init_FreeType(&m_Ft))
            ThrowInitializationException("Failed to initialize Freetype library!");

        // If font already loaded before, dont load again
        if (m_Fonts.count(fontFile))
            return m_Fonts[fontFile];

        // Load font
        FontFamily* fontFamily;
        FT_Face face;
        if (FT_New_Face(m_Ft, fontFile.c_str(), 0, &face))  // TODO: Think about 3rd parameter
            ThrowAEexceptionWMSG("Failed to load font: " + fontFile);

        fontFamily = new FontFamily();

        // Load glyph
        FT_Set_Pixel_Sizes(face, 0, 64);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 255; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                Logger::LogToFile("Failed to load glph!", "Logs.log", LogType::Warning);
                continue;
            }

            // Generate GL texture
            uint32_t texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(   GL_TEXTURE_2D,
                            0,
                            GL_RED,
                            face->glyph->bitmap.width,
                            face->glyph->bitmap.rows,
                            0,
                            GL_RED,
                            GL_UNSIGNED_BYTE,
                            face->glyph->bitmap.buffer);

            // Texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Store character for later use
            fontFamily->m_Chars.insert(std::pair<char, FontFamily::Character>(c, {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            }));
        }

        glBindTexture(GL_TEXTURE_2D, 0);

        FT_Done_Face(face);
        FT_Done_FreeType(m_Ft);

        m_Fonts[fontFile] = fontFamily;
        return fontFamily;
    }
}
