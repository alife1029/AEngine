#pragma once

#include <AEngine.hpp>

class AEditor : public aengine::Application
{
public:
    AEditor(const aengine::AppConfig& config);
    ~AEditor();
    void Start();
    void Update();
    void Dispose();
};
