#include "raylib.h"
#include "player.h"
#include "math.h"

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
