#include "AEngine/Graphics/RendererStat.hpp"

namespace aengine
{
    size_t RendererStat::mStaticQuadBatches = 0;
    size_t RendererStat::mStaticQuadCount = 0;
    size_t RendererStat::mDynamicQuadBatches = 0;
    size_t RendererStat::mDynamicQuadCount = 0;
    size_t RendererStat::mTextBatches = 0;
    size_t RendererStat::mTextQuadCount = 0;

    size_t RendererStat::VertexCount() noexcept
    {
        return (mDynamicQuadCount + mTextQuadCount + mStaticQuadCount) * 4;
    }
    size_t RendererStat::BatchCount() noexcept
    {
        return mDynamicQuadBatches + mTextBatches + mStaticQuadBatches + 2;
    }
    size_t RendererStat::VertexCount_Dynamic() noexcept
    {
        return (mDynamicQuadCount + mTextQuadCount) * 4;
    }
    size_t RendererStat::BatchCount_Dynamic() noexcept
    {
        return mDynamicQuadBatches + mTextBatches + 2;
    }
    size_t RendererStat::VertexCount_Static() noexcept
    {
        return mStaticQuadCount * 4;
    }
    size_t RendererStat::BatchCount_Static() noexcept
    {
        return mStaticQuadBatches;
    }
    size_t RendererStat::VertexCount_Quad() noexcept
    {
        return (mDynamicQuadCount + mStaticQuadCount) * 4;
    }
    size_t RendererStat::BatchCount_Quad() noexcept
    {
        return mDynamicQuadBatches + mStaticQuadBatches + 1;
    }
    size_t RendererStat::VertexCount_UIText() noexcept
    {
        return mTextQuadCount * 4;
    }
    size_t RendererStat::BatchCount_UIText() noexcept
    {
        return mTextBatches + 1;
    }

    void RendererStat::Reset() noexcept
    {
        mDynamicQuadBatches = 0;
        mDynamicQuadCount = 0;
        mTextBatches = 0;
        mTextQuadCount = 0;
    }
}
