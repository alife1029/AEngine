#ifndef AE_EVENT_SYSTEM_HPP
#define AE_EVENT_SYSTEM_HPP

#include "AE_API.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

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
        virtual void OnFocus(bool focused);
        void Flush();
    private:
        static Keyboard kbd;
        static Mouse mouse;
    
    private:
        class GLFWcallbacks
        {
        public:
            static EventSystem* eventSystemInstance;
            
            static void window_focus_callback(GLFWwindow*, int focused);
            static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
            static void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods);
            static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
            static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
            static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        };
    };
}

#endif
