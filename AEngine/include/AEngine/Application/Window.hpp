#ifndef AE_WINDOW_HPP
#define AE_WINDOW_HPP

#include <glm/vec2.hpp>
#include "AE_API.hpp"

struct GLFWwindow;

namespace aengine
{
    class AE_API Window
    {
        friend class Application;
    public:
        Window(int width, int height, const char* title, bool fullScreen);
        ~Window();

        bool IsOpen() const noexcept;
        
        void Clear() const noexcept;
        void SwapBuffers() const noexcept;
        void PollEvents() const noexcept;

        int Width() const noexcept;
        int Height() const noexcept;
        glm::ivec2 WindowSize() const noexcept;
    private:
        GLFWwindow* m_GlfwWindow;
    private:
        static void InitGLFW();
        static void TerminateGLFW();
        static void InitGLAD();
        static bool glfwInitialized;
        static bool gladInitialized;
    };
}

#endif
