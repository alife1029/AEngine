#ifndef AE_TEXTURE_2D_HPP
#define AE_TEXTURE_2D_HPP

#include "AE_API.hpp"

#include <cstdint>

namespace aengine
{
    class AE_API Texture2D
    {
    public:
        Texture2D() noexcept;
        Texture2D(const char* file, int pixelPerUnit = 100, bool forceRGBA = true);
        ~Texture2D();
        void LoadImage(const char* file, bool forceRGBA = true);
        void Activate() const noexcept;

        // Getters
        int Width() const noexcept;
        int Height() const noexcept;
        int ChannelCount() const noexcept;
        int PixelPerUnit() const noexcept;
        uint32_t ID() const noexcept;
        operator uint32_t() const noexcept;

        // Setters
        void SetPixelPerUnit(int amount) noexcept;
    private:
        uint32_t mId;
        int width;
        int height;
        int channelCount;
        int pixelPerUnit;
    public:
        static const Texture2D* WhiteTex() noexcept;
    private:
        static Texture2D* sWhiteTex;
    };
}

#endif
