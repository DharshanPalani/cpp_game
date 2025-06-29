#include "raylib.h"
#include "enemy.hpp"
#include <cmath>

Enemy::Enemy(float x, float y, int size, int speed, int health, Color color) 
    : x(x), y(y), size(size), speed(speed), health(health), color(color){}

void Enemy::Draw() {
    DrawCircle((int)x, (int)y, size, color);
}

Rectangle Enemy::GetRect() {
    return Rectangle{ x - size, y - size, float(size * 2), float(size * 2) };
}

bool Enemy::IsAlive() {
    return health > 0;
}

void Enemy::Damage() {
    health -= 1;
}

void Enemy::MoveTowardsPlayer(Vector2 playerVector)
{
    Vector2 direction ={playerVector.x - x, playerVector.y - y};
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction.x /= length;
        direction.y /= length;

        x += direction.x * speed;
        y += direction.y * speed;
    }
}
