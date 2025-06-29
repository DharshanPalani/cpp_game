#pragma once

#include <vector>
#include "raylib.h"
#include "../bullet/bullet.hpp"
#include <string>

class Player {
public:
    Player(float x, float y, int size, int speed, Color color);

    void Update();
    void Draw();
    void Shoot();
    Vector2 GetPosition() const;
    std::string GetBulletCount();
    Rectangle GetRect() const;
    void DrawHitBox(bool isColliding) const;

    std::vector<Bullet>& GetBullets();
    int bulletCount = 1000;

private:
    float x, y;
    int size;
    int speed;
    Color color;

    float timeSinceLastShot = 0.0f;
    std::vector<Bullet> bullets;
};
