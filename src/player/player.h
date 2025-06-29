#pragma once

#include <vector>

struct bullet {
    int x, y;
    float dx, dy;

    bullet(float x, float y, float dx, float dy)
        : x(x), y(y), dx(dx), dy(dy) {}
};

struct Player {
    int x;
    int y;
    int size;
    int speed;
    Color color;

    std::vector<bullet> bullets;

    void Update();
    void Draw();
    void Shoot();
};

