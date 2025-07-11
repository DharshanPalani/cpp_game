#pragma once

#include <vector>
#include "raylib.h"
#include "../bullet/bullet.hpp"
#include "../camera/camera.hpp"
#include <string>

class Player {
public:
    Player(float x, float y, int size, int speed, Color color);

    void Update(CameraShake& shake, Camera2D* camera);
    void Draw();
    void Shoot();
    void DrawHitBox(bool isColliding) const;
    void IncrementCoins(int coinAmountToIncrement);

    void IncrementAmmo();
    void IncrementHealth();

    void TakeDamage();
    void ResetPlayer();

    std::string GetBulletCount() const;
    std::string GetCoinCount() const;
    std::vector<Bullet>& GetBullets();
    Vector2 GetPosition() const;
    Rectangle GetRect() const;
    std::string GetHealth() const;
    bool IsAlive() const;


    int bulletCount = 10;

private:
    float x, y;
    int size;
    int speed;
    int coins = 10;
    int health = 3;
    bool isAlive = true;
    Color color;

    float timeSinceLastShot = 0.0f;
    std::vector<Bullet> bullets;
};
