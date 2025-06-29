#pragma once

#include <vector>
#include "raylib.h"
#include "../bullet/bullet.hpp"

class Player {
public:
    Player(float x, float y, int size, int speed, Color color);

    void Update();
    void Draw();
    void Shoot();
    Rectangle GetRect() const;
    void DrawHitBox(bool isColliding) const;

    std::vector<Bullet>& GetBullets();

private:
    float x, y;
    int size;
    int speed;
    Color color;

    float timeSinceLastShot = 0.0f;
    std::vector<Bullet> bullets;
};
