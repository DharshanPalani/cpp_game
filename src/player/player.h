#pragma once

#include <vector>
#include "raylib.h"

struct bullet {
    float x, y;
    float dx, dy;
    Rectangle GetRect();

    bullet(float x, float y, float dx, float dy)
        : x(x), y(y), dx(dx), dy(dy) {}
};

struct Player {
    float x;
    float y;
    int size;
    int speed;
    Color color;

    std::vector<bullet> bullets;

    void Update();
    void Draw();
    void Shoot();
    Rectangle GetRect();
    void DrawHitBox(bool isColliding);
};