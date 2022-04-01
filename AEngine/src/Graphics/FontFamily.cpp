#include "AEngine/Graphics/FontManager.hpp"
#include <glad/glad.h>

namespace aengine
{
    FontFamily::~FontFamily()
    {
        // Delete char textures from vram
        for (auto& [key, val] : m_Chars)
        {
            glDeleteTextures(1, &val.TextureID);
        }
    }
}
