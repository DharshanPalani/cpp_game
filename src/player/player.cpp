#include "player.hpp"
#include "math.h"
#include "../../config/playerConfig.h"
#include "../camera/camera.hpp"

Player::Player(float x, float y, int size, int speed, Color color)
    : x(x), y(y), size(size), speed(speed), color(color) {}

void Player::Update(CameraShake& shake, Camera2D* camera) {
    timeSinceLastShot += GetFrameTime();

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) x += speed;
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) x -= speed;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) y += speed;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) y -= speed;
    
    float delta = GetFrameTime();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && timeSinceLastShot >= PLAYER_FIRE_RATE) {
        if(bulletCount <= 0) return;
        shake.ShakeCamera(camera, 0.1f, 10, delta);
        Shoot();
        timeSinceLastShot = 0;
    } else {
        shake.ShakeCamera(camera, 0, 0, delta);
    }

    for (auto& bullet : bullets) {
        bullet.Update();
    }
}

void Player::Draw() {
    DrawRectangle((int)x, (int)y, size, size, color);
    for (auto& bullet : bullets) {
        bullet.Draw();
    }
}

void Player::Shoot() {

    

    Vector2 mousePos = GetMousePosition();

    float startX = x + size / 2;
    float startY = y + size / 2;

    float dirX = mousePos.x - startX;
    float dirY = mousePos.y - startY;
    float len = sqrt(dirX * dirX + dirY * dirY);
    dirX /= len;
    dirY /= len;

    bullets.emplace_back(startX, startY, dirX, dirY);

    bulletCount -= 1;
}

std::string Player::GetBulletCount() const
{
    return "Ammo: " + std::to_string(bulletCount);
}

Rectangle Player::GetRect() const {
    return Rectangle{ x, y, float(size), float(size) };
}

std::string Player::GetCoinCount() const
{
    return "Coin: " + std::to_string(coins);
}

void Player::DrawHitBox(bool isColliding) const {
    if (isColliding) {
        DrawRectangleLinesEx(GetRect(), 3, BLACK);
    }
}

void Player::IncrementCoins(int coinAmountToIncrement)
{
    coins = coins + coinAmountToIncrement;
}

std::vector<Bullet>& Player::GetBullets() {
    return bullets;
}

Vector2 Player::GetPosition() const {
    return {x, y};
}
