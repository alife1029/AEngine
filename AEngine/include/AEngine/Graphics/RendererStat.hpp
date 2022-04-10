#pragma once

#include "AE_API.hpp"
#include <cstdint>

namespace aengine
{
    class AE_API RendererStat
    {
        friend class Renderer2D;
        friend class Renderer2DStatic;
        friend class TextRenderer;
        friend class Application;
    public:
        static size_t VertexCount() noexcept;
        static size_t BatchCount() noexcept;
        static size_t VertexCount_Dynamic() noexcept;
        static size_t BatchCount_Dynamic() noexcept;
        static size_t VertexCount_Static() noexcept;
        static size_t BatchCount_Static() noexcept;
        static size_t VertexCount_Quad() noexcept;
        static size_t BatchCount_Quad() noexcept;
        static size_t VertexCount_UIText() noexcept;
        static size_t BatchCount_UIText() noexcept;
    private:
        static void Reset() noexcept;
    private:
        static size_t mDynamicQuadBatches;
        static size_t mDynamicQuadCount;
        static size_t mStaticQuadBatches;
        static size_t mStaticQuadCount;
        static size_t mTextBatches;
        static size_t mTextQuadCount;
    };
}
