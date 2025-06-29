#include "raylib.h"
#include "player.h"
#include "math.h"

float timeSinceLastShot = 0;
float fireRate = 0.5;

void Player::Update() {

    timeSinceLastShot += GetFrameTime();

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) x += speed;
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) x -= speed;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) y += speed;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) y -= speed;
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && timeSinceLastShot >= fireRate) {
        Shoot();
        timeSinceLastShot = 0;
    } 

    for(auto&bullet : bullets) {
        bullet.x += bullet.dx * 10;
        bullet.y += bullet.dy * 10;
    }
}

void Player::Draw() {
    DrawRectangle(x,y,size,size, color);
    for (auto& bullet : bullets) {
        DrawCircle(static_cast<int>(bullet.x), static_cast<int>(bullet.y), 5, RED);
    }
}

void Player::Shoot() {
    Vector2 mousePos = GetMousePosition();

    float startX = x + size / 2;
    float startY = y + size / 2;

    float directionX = mousePos.x - startX;
    float directionY = mousePos.y - startY;
    float length = sqrt(directionX * directionX + directionY * directionY);
    directionX = directionX / length;
    directionY = directionY / length;

    bullets.push_back({ startX, startY, directionX, directionY});
}

