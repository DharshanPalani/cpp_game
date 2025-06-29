#include "raylib.h"
#include "enemy.hpp"

Enemy::Enemy(float x, float y, int size, int speed, int health, Color color) 
    : x(x), y(y), size(size), speed(speed), health(health), color(color){}

void Enemy::Draw() {
    DrawCircle((int)x, (int)y, size, color);
}

Rectangle Enemy::GetRect() {
    return Rectangle{ x - size, y - size, float(size * 2), float(size * 2) };
}

bool Enemy::IsAlive() {
    return health <= 0;
}

void Enemy::Damage() {
    health -= 1;
}