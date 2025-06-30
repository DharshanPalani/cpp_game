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

    // if(IsKeyPressed(KEY_R)) {
    //     if(coins > 0) {
    //         coins = coins - 1;
    //         bulletCount = bulletCount + 3;
    //     }
    // }
    
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

void Player::ResetPlayer()
{
    health = 3;
    coins = 0;
    bulletCount = 10;
    isAlive = true;
    x = 300;
    y = 300;
}

void Player::TakeDamage()
{
    health = health - 1;

    if(health <= 0) {
        // TODO: Add death system later;
        isAlive = false;
    }
}

bool Player::IsAlive() const {
    return isAlive;
}

Rectangle Player::GetRect() const {
    return Rectangle{ x, y, float(size), float(size) };
}

std::string Player::GetHealth() const
{
    return "Health: " + std::to_string(health);
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

void Player::IncrementAmmo()
{
    if(coins <= 0) return;

    coins = coins - 1;
    bulletCount = bulletCount + 3;
}

void Player::IncrementHealth()
{
    if(coins >= 3) return;

    coins = coins - 3;
    health = health + 1;
}

std::vector<Bullet>& Player::GetBullets() {
    return bullets;
}

Vector2 Player::GetPosition() const {
    return {x, y};
}
