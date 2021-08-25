#ifndef AED_INSPECTOR_PANEL_HPP
#define AED_INSPECTOR_PANEL_HPP

#include <AEngine.hpp>
#include "Panel.hpp"

using namespace aengine;

class InspectorPanel : public Panel
{
public:
    Entity** currentEntityPPtr;
public:
    void Render();
};

#endif
