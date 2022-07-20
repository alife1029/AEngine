#pragma once

#include <AEngine.hpp>

class AEditor : public aengine::Application
{
public:
    AEditor(const AppConfig& config);
    ~AEditor();
    void Start();
    void Update();
    void Dispose();
};
