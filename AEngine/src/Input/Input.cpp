#include "AEngine/Input/Input.hpp"
#include "AEngine/Input/EventSystem.hpp"

#include <GLFW/glfw3.h>

namespace aengine
{
    EventSystem* Input::mEventSystem = nullptr;

    bool Input::IsKeyPressing(Key key)
    {
        return (bool)mEventSystem->kbd.IsPressing((int)key);
    }

    bool Input::IsKeyJustPressed(Key key)
    {
        return mEventSystem->kbd.IsJustReleased((int)key);
    }

    bool Input::IsKeyJustReleased(Key key)
    {
        return mEventSystem->kbd.IsJustReleased((int)key);
    }
}
