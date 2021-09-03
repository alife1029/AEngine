#include "CameraController.hpp"

void CameraController::Update()
{
    // Moving camera
    float currCmrSpeed = cameraSpeed * (float)Time::DeltaTime();
    float currCmrRotSpeed = cameraRotSpeed * (float)Time::DeltaTime();

    if (Input::IsKeyPressing(Key::A))
        camera->Translate(-currCmrSpeed, 0.0f);
    if (Input::IsKeyPressing(Key::D))
        camera->Translate(currCmrSpeed, 0.0f);
    if (Input::IsKeyPressing(Key::W))
        camera->Translate(0.0f, currCmrSpeed);
    if (Input::IsKeyPressing(Key::S))
        camera->Translate(0.0f, -currCmrSpeed);
    if (Input::IsKeyPressing(Key::Q))
        camera->Rotate(currCmrRotSpeed);
    if (Input::IsKeyPressing(Key::E))
        camera->Rotate(-currCmrRotSpeed);
}

GETTYPE_IMP(CameraController)
