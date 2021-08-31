#include "AEngine/Input/Input.hpp"
#include "AEngine/Input/EventSystem.hpp"

#include <GLFW/glfw3.h>

namespace aengine
{
    EventSystem* Input::mEventSystem = nullptr;

    bool Input::IsKeyPressing(Key key) noexcept
    {
        return (bool)mEventSystem->kbd.IsPressing((int)key);
    }

    bool Input::IsKeyJustPressed(Key key) noexcept
    {
        return mEventSystem->kbd.IsJustReleased((int)key);
    }

    bool Input::IsKeyJustReleased(Key key) noexcept
    {
        return mEventSystem->kbd.IsJustReleased((int)key);
    }



    // Mouse
    const glm::dvec2& Input::CursorPosition() noexcept
    {
        return mEventSystem->mouse.CursorPosition();
    }
    const glm::dvec2& Input::CursorDelta() noexcept
    {
        return mEventSystem->mouse.CursorDelta();
    }
    glm::dvec2 Input::CursorDragDelta(MouseButton button) noexcept
    {
        return mEventSystem->mouse.DragDelta(button);
    }

    bool Input::IsJustClicked(MouseButton button) noexcept
    {
        return mEventSystem->mouse.IsJustClicked(button);
    }
    bool Input::IsClicking(MouseButton button) noexcept
    {
        return mEventSystem->mouse.IsClicking(button);
    }
    bool Input::IsDoubleClicked(MouseButton button) noexcept
    {
        return mEventSystem->mouse.IsDoubleClicked(button);
    }
    double Input::ScrollY() noexcept
    {
        return mEventSystem->mouse.ScrollY();
    }
    double Input::ScrollX() noexcept
    {
        return mEventSystem->mouse.ScrollX();
    }
    const glm::dvec2& Input::Scroll() noexcept
    {
        return mEventSystem->mouse.Scroll();
    }
}
