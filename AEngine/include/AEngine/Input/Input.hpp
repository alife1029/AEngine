#ifndef AE_INPUT_HPP
#define AE_INPUT_HPP

#include "AE_API.hpp"
#include "Keys.hpp"
#include "Buttons.hpp"
#include <glm/vec2.hpp>

namespace aengine
{
    class EventSystem;
    class AE_API Input
    {
        friend class Application;
    public:
        // Keyboard
        static bool IsKeyPressing(Key key) noexcept;
        static bool IsKeyJustPressed(Key key) noexcept;
        static bool IsKeyJustReleased(Key key) noexcept;

        // Mouse
        // Cursor getters
        static const glm::dvec2& CursorPosition() noexcept;
        static const glm::dvec2& CursorDelta() noexcept;
        static glm::dvec2 CursorDragDelta(MouseButton button) noexcept;
        // Button getters
        static bool IsJustClicked(MouseButton button) noexcept;
        static bool IsClicking(MouseButton button) noexcept;
        static bool IsDoubleClicked(MouseButton button) noexcept;
        static double ScrollY() noexcept;
        static double ScrollX() noexcept;
        static const glm::dvec2& Scroll() noexcept;
    private:
        static EventSystem* mEventSystem;
    };
}

#endif
