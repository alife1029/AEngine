#ifndef AE_VIEWPORT_HPP
#define AE_VIEWPORT_HPP

#include "AE_API.hpp"

namespace aengine
{
    class AE_API Viewport
    {
    public:
        enum class Type { Stretch, Fill, Fit };
    public:
        Viewport(int virtualW, int virtualH, Type type = Type::Fill) noexcept;
        void Update(int w, int h) noexcept;
        void Update(int x, int y, int w, int h) noexcept;
        float Aspect() const noexcept;
        int X() const noexcept;
        int Y() const noexcept;
        int Width() const noexcept;
        int Height() const noexcept;
        Type GetType() const noexcept;
    private:
        float mAspect;
        int mX;
        int mY;
        int mW;
        int mH;
        Type mType;
    };
}

#endif
