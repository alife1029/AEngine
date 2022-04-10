#include "AEngine/Graphics/RendererStat.hpp"

namespace aengine
{
    uint32_t RendererStat::mQuadBatches = 0;
    uint32_t RendererStat::mQuadCount = 0;
    uint32_t RendererStat::mTextBatches = 0;
    uint32_t RendererStat::mTextQuadCount = 0;

    uint32_t RendererStat::VertexCount() noexcept
    {
        return (mQuadCount + mTextQuadCount) * 4;
    }
    uint32_t RendererStat::BatchCount() noexcept
    {
        return mQuadBatches + mTextBatches + 2;
    }
    uint32_t RendererStat::VertexCount_Quad() noexcept
    {
        return mQuadCount * 4;
    }
    uint32_t RendererStat::BatchCount_Quad() noexcept
    {
        return mQuadBatches + 1;
    }
    uint32_t RendererStat::VertexCount_UIText() noexcept
    {
        return mTextQuadCount * 4;
    }
    uint32_t RendererStat::BatchCount_UIText() noexcept
    {
        return mTextBatches + 1;
    }

    void RendererStat::Reset() noexcept
    {
        mQuadBatches = 0;
        mQuadCount = 0;
        mTextBatches = 0;
        mTextQuadCount = 0;
    }
}
