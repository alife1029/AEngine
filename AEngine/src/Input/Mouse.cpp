#include "AEngine/Input/Mouse.hpp"
#include "AEngine/Utils/Time.hpp"

namespace aengine
{
    // Cursor
    const glm::dvec2& Mouse::CursorPosition() const noexcept
    {
        return cursorPos;
    }
    const glm::dvec2& Mouse::CursorDelta() const noexcept
    {
        return cursorDelta;
    }

    // Drag
    glm::dvec2 Mouse::DragDelta(MouseButton button) const noexcept
    {
        if (buttons[(size_t)button])
        { 
            return cursorDelta;
        }

        return { 0.0, 0.0 };
    }

    // Button click
    bool Mouse::IsJustClicked(MouseButton button) const noexcept
    {
        return buttons[(size_t)button] && !lastButtons[(size_t)button];
    }
    bool Mouse::IsClicking(MouseButton button) const noexcept
    {
        return buttons[(size_t)button];
    }
    bool Mouse::IsDoubleClicked(MouseButton button) const noexcept
    {
        return buttons[(size_t)button] && lastClickTimes[(size_t)button] < 0.5;
    }

    double Mouse::ScrollY() const noexcept
    {
        return scroll.y;
    }
    double Mouse::ScrollX() const noexcept
    {
        return scroll.x;
    }
    const glm::dvec2& Mouse::Scroll() const noexcept
    {
        return scroll;
    }

    void Mouse::Flush()
    {
        double dt = Time::DeltaTime();

        lastButtons = buttons;
        cursorDelta = { 0.0, 0.0 };
        scroll = { 0.0, 0.0 };
        for (size_t i = 0; i < buttonCount; i++) 
        {
            lastClickTimes[i] += dt; // Update last click times
        }
    }

    void Mouse::OnButtonPress(int code)
    {
        buttons[code] = true;
    }
    void Mouse::OnButtonRelease(int code)
    {
        buttons[code] = false;
    }
    void Mouse::OnCursorMoved(double x, double y)
    {
        cursorDelta = { x - cursorPos.x, y - cursorPos.y };
        cursorPos = { x, y };
    }
    void Mouse::OnScrolled(double x, double y)
    {
        scroll = { x, y };
    }
}
