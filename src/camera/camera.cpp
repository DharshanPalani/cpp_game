#include "camera.hpp"
#include <cstdlib>

CameraShake::CameraShake()
    : shakeTime(0.0f), shakeDuration(0.0f), shakeStrength(0.0f), originalOffset({0, 0}), shaking(false) {}

void CameraShake::ShakeCamera(Camera2D* camera, float duration, float strength, float deltaTime) {
    if (!shaking && duration > 0.0f) {
        shakeDuration = duration;
        shakeStrength = strength;
        shakeTime = 0.0f;
        originalOffset = camera->offset;
        shaking = true;
    }

    if (shaking) {
        shakeTime += deltaTime;

        if (shakeTime < shakeDuration) {
            float shakeX = ((float)rand() / RAND_MAX * 2 - 1) * shakeStrength;
            float shakeY = ((float)rand() / RAND_MAX * 2 - 1) * shakeStrength;
            camera->offset = { originalOffset.x + shakeX, originalOffset.y + shakeY };
        } else {
            camera->offset = originalOffset;
            shaking = false;
        }
    }
}
