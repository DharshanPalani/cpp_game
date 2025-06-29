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
    void DrawHitBox(bool isColliding) const;
    void IncrementCoins(int coinAmountToIncrement);

    std::string GetBulletCount() const;
    std::string GetCoinCount() const;
    std::vector<Bullet>& GetBullets();
    Vector2 GetPosition() const;
    Rectangle GetRect() const;


    int bulletCount = 1000;

private:
    float x, y;
    int size;
    int speed;
    int coins = 10;
    Color color;

    float timeSinceLastShot = 0.0f;
    std::vector<Bullet> bullets;
};
