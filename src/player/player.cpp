#include "player.h"
#include "math.h"
#include "../../config/playerConfig.h"

Player::Player(float x, float y, int size, int speed, Color color)
    : x(x), y(y), size(size), speed(speed), color(color) {}

void Player::Update() {
    timeSinceLastShot += GetFrameTime();

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) x += speed;
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) x -= speed;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) y += speed;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) y -= speed;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && timeSinceLastShot >= PLAYER_FIRE_RATE) {
        Shoot();
        timeSinceLastShot = 0;
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
}

Rectangle Player::GetRect() const {
    return Rectangle{ x, y, float(size), float(size) };
}

void Player::DrawHitBox(bool isColliding) const {
    if (isColliding) {
        DrawRectangleLinesEx(GetRect(), 3, BLACK);
    }
}

std::vector<Bullet>& Player::GetBullets() {
    return bullets;
}
