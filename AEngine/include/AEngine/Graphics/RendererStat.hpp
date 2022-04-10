#pragma once

#include "AE_API.hpp"
#include <cstdint>

namespace aengine
{
    class AE_API RendererStat
    {
        friend class Renderer2D;
        friend class TextRenderer;
        friend class Application;
    public:
        static uint32_t VertexCount() noexcept;
        static uint32_t BatchCount() noexcept;
        static uint32_t VertexCount_Quad() noexcept;
        static uint32_t BatchCount_Quad() noexcept;
        static uint32_t VertexCount_UIText() noexcept;
        static uint32_t BatchCount_UIText() noexcept;
    private:
        static void Reset() noexcept;
    private:
        static uint32_t mQuadBatches;
        static uint32_t mQuadCount;
        static uint32_t mTextBatches;
        static uint32_t mTextQuadCount;
    };
}
