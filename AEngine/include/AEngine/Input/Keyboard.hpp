#ifndef AE_INPUT_KEYBOARD_HPP
#define AE_INPUT_KEYBOARD_HPP

#include "AE_API.hpp"
#include <bitset>

namespace aengine
{
    class AE_API Keyboard
    {
        friend class EventSystem;
    public:
        bool IsPressing(int keycode);
        bool IsJustPressed(int keycode);
        bool IsJustReleased(int keycode);
        void Flush();
    private:
        void OnKeyPress(int keycode);
        void OnKeyRelease(int keycode);
    private:
        static const unsigned int maxKey = 348;  
        std::bitset<maxKey> keys;
        std::bitset<maxKey> lastKeys;
    };
}

#endif
