#pragma once
#include "Prelude.hpp"
#include "Camera2D.hpp"


class MyCamera : public Camera2D
{
    GODOT_CLASS(MyCamera, Camera2D)

 public:
    _EMPTY_INIT()
    _REGISTER_METHODS()
    _PROCESS()
    _READY()
    _UNHANDLED_INPUT()

    MyCamera();

    float Speed;
    float MoveThreshold;
    Vector2 WinSize{};

    void OnSizeChange();

 private:
    float MoveThresholdPercentage;

    void ZoomCamera(float zoomSpeed, Vector2 position);
};