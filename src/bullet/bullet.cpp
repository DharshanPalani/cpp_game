#include "bullet.hpp"

Bullet::Bullet(float x, float y, float dx, float dy) : x(x), y(y), dx(dx), dy(dy) {}

void Bullet::Update(float speed) {
    x += dx * speed;
    y += dy * speed;
}

void Bullet::Draw() const {
    DrawCircle((int)x, (int)y, radius, RED);
}

Rectangle Bullet::GetRect() const {
    return Rectangle{ x - radius, y - radius, radius * 2, radius * 2 };
}

Vector2 Bullet::GetPosition() const {
    return {x, y};
}