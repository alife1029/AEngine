#ifndef AED_AEDITOR_HPP
#define AED_AEDITOR_HPP

#include <AEngine.hpp>
#include "Menus/Menu.hpp"

using namespace aengine;

class AEditor : public Application
{
private:
    Menu* mActiveMenu;
public:
    AEditor(const AppConfig& config);
    ~AEditor();
    void Start();
    void Update();
    void Dispose();
};

#endif
