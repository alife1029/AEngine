#ifndef AE_EVENT_SYSTEM_HPP
#define AE_EVENT_SYSTEM_HPP

#include "AE_API.hpp"
#include "Keyboard.hpp"

struct GLFWwindow;

namespace aengine
{
    class Application;
    
    class AE_API EventSystem
    {
        friend class Input;
    public:
        void SetEventListener(Application* appInstance);
        virtual void OnResize(int width, int height);
        static Keyboard kbd;
    private:
        class GLFWcallbacks
        {
        public:
            static EventSystem* eventSystemInstance;
            static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
            static void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods);
        };
    };
}

#endif
