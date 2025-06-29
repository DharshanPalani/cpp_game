#include "raylib.h"
#include "player.h"
#include "math.h"
#include "../../config/playerConfig.h"

float timeSinceLastShot = 0;

void Player::Update() {

    timeSinceLastShot += GetFrameTime();

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) x += speed;
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) x -= speed;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) y += speed;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) y -= speed;

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && timeSinceLastShot >= PLAYER_FIRE_RATE) {
        Player::Shoot();
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