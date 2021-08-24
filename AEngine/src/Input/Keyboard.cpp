#include "AEngine/Input/Keyboard.hpp"
#include <iostream>

namespace aengine
{
    bool Keyboard::IsPressing(int keycode)
    {
        return keys[keycode];
    }
    bool Keyboard::IsJustPressed(int keycode)
    {
        std::cout << "IsKeyJustPressed" << std::endl
            << "Keycode: " << (int)keycode << std::endl
            << "keys[keycode] " << (bool)keys[keycode] << std::endl
            << "lastKeys[keycode] " << (bool)keys[keycode] << std::endl;
        return keys[keycode] && !lastKeys[keycode];
    }
    bool Keyboard::IsJustReleased(int keycode)
    {
        return !keys[keycode] && lastKeys[keycode];
    }

    void Keyboard::Flush()
    {
        lastKeys = keys;
    }
    void Keyboard::OnKeyPress(int keycode)
    {
        keys[keycode] = true;
    }
    void Keyboard::OnKeyRelease(int keycode)
    {
        keys[keycode] = false;
    }
}
