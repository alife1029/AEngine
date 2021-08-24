#ifndef AE_INPUT_HPP
#define AE_INPUT_HPP

#include "AE_API.hpp"
#include "Keys.hpp"

namespace aengine
{
    class EventSystem;
    class AE_API Input
    {
        friend class Application;
    public:
        static bool IsKeyPressing(Key key);
        static bool IsKeyJustPressed(Key key);
        static bool IsKeyJustReleased(Key key);
    private:
        static EventSystem* mEventSystem;
    };
}

#endif
