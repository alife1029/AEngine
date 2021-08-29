#include "AEngine/Utils/Time.hpp"
#include <GLFW/glfw3.h>

namespace aengine
{
    double Time::lastFrame = 0.0;
    double Time::deltaTime = 0.0;

    void Time::Update()
    {
        deltaTime = glfwGetTime() - lastFrame;
        lastFrame += deltaTime;
    }

    double Time::DeltaTime()
    {
        return lastFrame > 0.0 ? deltaTime : 1.0 / 60.0;
    }

    float Time::DeltaTimeF()
    {
        return static_cast<float>(DeltaTime());
    }
}
