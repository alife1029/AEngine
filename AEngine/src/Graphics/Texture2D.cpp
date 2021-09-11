#include "AEngine/Graphics/Texture2D.hpp"
#include "AEngine/Exception/Exception.hpp"
#include "AEngine/Utils/Logger.hpp"

#include <glad/glad.h>
#include <stb/stb_image.h>

namespace aengine
{
    Texture2D::Texture2D() noexcept
    {
        glGenTextures(1, &mId);
    }

    Texture2D::Texture2D(const char* file, int pixelPerUnit, bool forceRGBA)
        : pixelPerUnit(pixelPerUnit)
    {
        glGenTextures(1, &mId);
        LoadImage(file, forceRGBA);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &mId);
    }

    void Texture2D::LoadImage(const char* file, bool forceRGBA)
    {
        GLint imageFormat;
        unsigned char* pixels;
        
        stbi_set_flip_vertically_on_load(1);
        pixels = stbi_load(file, &width, &height, &channelCount, forceRGBA ? STBI_rgb_alpha : 0);
        if (!pixels)
            ThrowAEexceptionWMSG(std::string(file) + " not found!");

        // Detect image format
        if (!forceRGBA)
        {
            switch (channelCount)
            {
            case 4:
                imageFormat = GL_RGBA;
                break;
            case 3:
                imageFormat = GL_RGB;
                break;
            case 2:
                imageFormat = GL_RG;
                break;
            case 1:
                imageFormat = GL_RED;
                break;
            default:
                ThrowAEexceptionWMSG("Unsupported channel count in image file (" + std::string(file) + ")");
            }
        }
        else
        {
            imageFormat = GL_RGBA;
        }
        
        glBindTexture(GL_TEXTURE_2D, mId);
        glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(pixels);
    }

    void Texture2D::Activate() const noexcept
    {
        glBindTexture(GL_TEXTURE_2D, mId);
    }

    int Texture2D::Width() const noexcept
    {
        return width;
    }

    int Texture2D::Height() const noexcept
    {
        return height;
    }

    int Texture2D::ChannelCount() const noexcept
    {
        return channelCount;
    }

    int Texture2D::PixelPerUnit() const noexcept
    {
        return pixelPerUnit;
    }

    uint32_t Texture2D::ID() const noexcept
    {
        return mId;
    }

    Texture2D::operator uint32_t() const noexcept
    {
        return mId;
    }

    void Texture2D::SetPixelPerUnit(int amount) noexcept
    {
        pixelPerUnit = amount;
    }

    Texture2D* Texture2D::sWhiteTex = nullptr;
    const Texture2D* Texture2D::WhiteTex() noexcept
    {
        if (sWhiteTex == nullptr)
        {
            // Generate white texture
            sWhiteTex = new Texture2D();
            glGenTextures(1, &sWhiteTex->mId);
            glBindTexture(GL_TEXTURE_2D, sWhiteTex->ID());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            
            // Load texture data
            uint32_t color = 0xffffffff;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);
            glBindTexture(GL_TEXTURE_2D, 0);
            sWhiteTex->channelCount = 4;
            sWhiteTex->width = 1;
            sWhiteTex->height = 1;
            sWhiteTex->pixelPerUnit = 1;
        }
        
        return sWhiteTex;
    }
}
