#pragma once

#include "AEngine.hpp"

using namespace aengine;

class CameraController : public Component
{
public:
    OrthographicCamera* camera;
    float cameraSpeed = 1.0f;
    float cameraRotSpeed = 31.31f;
public:
    void Update();
    GETTYPE_DEC();
};
