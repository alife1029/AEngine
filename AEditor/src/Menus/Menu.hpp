#ifndef AED_MENU_HPP
#define AED_MENU_HPP

#include <AEngine.hpp>

class Menu
{
protected:
    aengine::Application* mApp;
public:
    Menu(aengine::Application* app);
    virtual void Start();
    virtual void Update();
    virtual void Dispose();
};

#endif
