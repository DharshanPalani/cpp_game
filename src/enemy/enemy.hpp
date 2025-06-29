#pragma once

#include "raylib.h"

class Enemy {
public:
    Enemy(float x, float y, int size, int speed, Color color);
    void Draw();
    Rectangle GetRect();

private:
    float x,y;
    int size;
    int speed;
    Color color;
};