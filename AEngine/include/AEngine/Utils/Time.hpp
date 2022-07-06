#ifndef AE_TIME_HPP
#define AE_TIME_HPP

#include "AE_API.hpp"

namespace aengine
{
    class AE_API Time
    {
        friend class Application;
        friend class CustomFileDialog;
    public:
        static double DeltaTime();
        static float DeltaTimeF();
    private:
        static void Update();
    private:
        static double lastFrame;
        static double deltaTime;
    };
}

#endif
