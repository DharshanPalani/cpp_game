#pragma once

#include "raylib.h"

class Bullet {
public:
    Bullet(float x, float y, float dx, float dy);

    void Update(float speed = 10.0f);
    void Draw() const;
    Rectangle GetRect() const;
    Vector2 GetPosition() const;

private:
    float x, y;
    float dx, dy;
    float radius = 5.0f;
};
