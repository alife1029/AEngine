#ifndef AE_INPUT_MOUSE_HPP
#define AE_INPUT_MOUSE_HPP

#include "AE_API.hpp"
#include "Buttons.hpp"
#include <glm/vec2.hpp>
#include <bitset>
#include <array>

namespace aengine
{
    class AE_API Mouse
    {
        friend class EventSystem;
    public:
        // Cursor getters
        const glm::dvec2& CursorPosition() const noexcept;
        const glm::dvec2& CursorDelta() const noexcept;
        glm::dvec2 DragDelta(MouseButton button) const noexcept;

        // Button getters
        bool IsJustClicked(MouseButton button) const noexcept;
        bool IsClicking(MouseButton button) const noexcept;
        bool IsDoubleClicked(MouseButton button) const noexcept;
        double ScrollY() const noexcept;
        double ScrollX() const noexcept;
        const glm::dvec2& Scroll() const noexcept;

        void Flush();

    private:
        void OnButtonPress(int code);
        void OnButtonRelease(int code);
        void OnCursorMoved(double x, double y);
        void OnScrolled(double x, double y);

    private:
        static constexpr size_t buttonCount = 8;

        // Cursor
        glm::dvec2 cursorPos = { 0.0, 0.0 };
        glm::dvec2 cursorDelta = { 0.0, 0.0 };
        glm::dvec2 scroll = { 0.0, 0.0 };

        // Mouse button clicks
        std::bitset<buttonCount> buttons;
        std::bitset<buttonCount> lastButtons;
        std::array<double, buttonCount> lastClickTimes;
    };
}

#endif
