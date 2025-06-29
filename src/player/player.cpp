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
    
    
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i].x += bullets[i].dx * 10;
        bullets[i].y += bullets[i].dy * 10;

        Rectangle target = {200, 200, 50, 50};

        // Check bullet collision with the object
        if (CheckCollisionCircleRec({ bullets[i].x, bullets[i].y }, 5, target)) {
            // Remove bullet
            bullets.erase(bullets.begin() + i);
            i--; // Decreasing coz bullet is removed
        }
    }
}

void Player::Draw() {
    DrawRectangle(x,y,size,size, color);
    for (auto& bullet : bullets) {
        DrawCircle(static_cast<int>(bullet.x), static_cast<int>(bullet.y), 5, RED);
    }
}

Rectangle Player::GetRect() {
    return Rectangle{x, y, float(size), float(size)};
}

void Player::DrawHitBox(bool isColliding) {

    if(isColliding == true) {
        DrawRectangleLinesEx(GetRect(), 3, BLACK);
    }
}