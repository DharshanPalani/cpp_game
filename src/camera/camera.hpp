#pragma once

#include "raylib.h"

class CameraShake {
public:
    CameraShake();

    void ShakeCamera(Camera2D* camera, float duration, float strength, float deltaTime);

private:
    float shakeTime;
    float shakeDuration;
    float shakeStrength;
    Vector2 originalOffset;
    bool shaking;
};
