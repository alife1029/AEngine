#ifndef AE_APPLICATION_HPP
#define AE_APPLICATION_HPP

// Application entry point

#include "AE_API.hpp"
#include "Window.hpp"
#include "AppConfig.hpp"
#include "../Input/EventSystem.hpp"
#include "../Graphics/OrhographicCamera.hpp"

namespace aengine
{
    class AE_API Application : public EventSystem
    {
        friend class EventSystem;
    public:
        Application(const AppConfig& config);
        ~Application();

        void Run();

        void BindMainCamera(OrthographicCamera* camera) noexcept;
        OrthographicCamera* GetMainCamera() const noexcept;

        virtual void Start();
        virtual void Update();
        virtual void Dispose();

        virtual void OnResize(int width, int height);
        virtual void OnFocus(bool focused);
        
        GLFWwindow* GetGLFWwindow();
        bool IsFocused();
    
    protected:
        Window* m_Window;

    private:
        OrthographicCamera* m_MainCamera;
        EventSystem mEventSystem;
        bool focused = true;
    };
}

#endif
