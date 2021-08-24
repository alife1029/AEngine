#include "AEngine/Graphics/Viewport.hpp"
#include <glad/glad.h>
#include <cmath>

namespace aengine
{
    Viewport::Viewport(int virtualW, int virtualH, Type type) noexcept
        : mX(0), mY(0), mW(virtualW), mH(virtualH), mType(type)
    {
        mAspect = (float)mW / (float)mH;
        Update(mW, mH);
    }

    void Viewport::Update(int w, int h) noexcept
    {
        switch (mType)
        {
        case Type::Stretch:
            glViewport(0, 0, w, h);
            break;

        case Type::Fill:
            mX = 0;
            mY = 0;
            mW = w;
            mH = h;
            mAspect = (float)mW / (float)mH;
            glViewport(mX, mY, mW, mH);
            break;

        case Type::Fit:
            float newAspect = static_cast<float>(w) / static_cast<float>(h);

            if (newAspect >= mAspect)
            {
                mW = static_cast<int>(h * mAspect);
                mH = h;
                mX = (w - mW) / 2;
                mY = 0;
            }
            else
            {
                mW = w;
                mH = static_cast<int>(w * pow(mAspect, -1.0));
                mX = 0;
                mY = (h - mH) / 2;
            }
            glViewport(mX, mY, mW, mH);
            break;
        }
    }

    void Viewport::Update(int x, int y, int w, int h) noexcept
    {
        mX = x;
        mY = y;
        mW = w;
        mH = h;
        mAspect = (float)mW / (float)mH;
        glViewport(mX, mY, mW, mH);
    }

    float Viewport::Aspect() const noexcept
    {
        return mAspect;
    }
    int Viewport::X() const noexcept
    {
        return mX;
    }
    int Viewport::Y() const noexcept
    {
        return mY;
    }
    int Viewport::Width() const noexcept
    {
        return mW;
    }
    int Viewport::Height() const noexcept
    {
        return mH;
    }
    Viewport::Type Viewport::GetType() const noexcept
    {
        return mType;
    }
}
