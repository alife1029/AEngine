#ifndef AED_AEDITOR_HPP
#define AED_AEDITOR_HPP

#include <AEngine.hpp>
#include "Menus/Menu.hpp"
#include "Core/Project.hpp"

using namespace aengine;

class AEditor : public Application
{
private:
    Menu* mActiveMenu;
    AEProject* mActiveProject;
public:
    AEditor(const AppConfig& config);
    ~AEditor();
    void Start();
    void Update();
    void Dispose();
};

#endif
