#include "AEngine/Graphics/FontManager.hpp"
#include "AEngine/Exception/InitializationException.hpp"

namespace aengine
{
    void FontManager::Initialize()
    {
        if (FT_Init_FreeType(&m_Ft))
            ThrowInitializationException("Failed to initialize Freetype library!");
    }

    void FontManager::Shutdown()
    {

    }

    FontFamily* FontManager::LoadFont(const std::string& fontFile)
    {
        // If font already loaded before, dont load again
        if (m_Fonts.count(fontFile))
            return m_Fonts[fontFile];

        // Load font
        FT_Face face;
        if (FT_New_Face(m_Ft, fontFile.c_str(), 0, &face))  // TODO: Think about 3rd parameter
        {

        }
    }
}
