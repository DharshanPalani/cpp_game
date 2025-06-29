#pragma once

#include "raylib.h"

class Enemy {
public:
    Enemy(float x, float y, int size, int speed, int health, Color color);
    void Draw();
    void Damage();
    void MoveTowardsPlayer(Vector2 playerVector);
    bool IsAlive();
    Rectangle GetRect();

private:
    float x,y;
    int size;
    int speed;
    int health = 1;
    Color color;
};