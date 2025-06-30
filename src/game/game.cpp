#include "game.hpp"
#include "../../config/playerConfig.h"
#include <cmath>

Game::Game(Player& playerRef) : player(playerRef) {
    enemies.push_back(Enemy(100, 100, 30, 2, 1, RED));
    enemies.push_back(Enemy(200, 200, 20, 4, 1, BLACK));
    enemies.push_back(Enemy(400, 200, 40, 1, 1, PURPLE));
    
}
void Game::Update(CameraShake& shake, Camera2D* camera) {
    player.Update(shake, camera);
    player.Draw();
    for (int i = 0; i < enemies.size(); ++i) {
    if (!enemies[i].IsAlive()) continue;

    bool isColliding = false;

    for (int j = 0; j < enemies.size(); ++j) {
        if (i == j) continue;

        if (CheckCollisionRecs(enemies[i].GetRect(), enemies[j].GetRect())) {
            isColliding = true;
            break;
        }
    }

    enemies[i].Draw();

    if (!isColliding) {
        enemies[i].MoveTowardsPlayer(player.GetPosition());
    }
}


    for (size_t i = 0; i < enemies.size(); i++) {
    for (size_t j = i + 1; j < enemies.size(); j++) {

        if (!enemies[i].IsAlive() || !enemies[j].IsAlive()) continue;

        if (CheckCollisionRecs(enemies[i].GetRect(), enemies[j].GetRect())) {
            Vector2 dir = {
                enemies[i].GetPosition().x - enemies[j].GetPosition().x,
                enemies[i].GetPosition().y - enemies[j].GetPosition().y
            };

            if (dir.x == 0 && dir.y == 0)
                dir = { 1.0f, 0.0f };

            float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
            dir.x /= len;
            dir.y /= len;

            float pushAmount = 0.5f;

            enemies[i].Move(dir.x * pushAmount, dir.y * pushAmount);
            enemies[j].Move(-dir.x * pushAmount, -dir.y * pushAmount);
        }
    }
}



    auto& bullets = player.GetBullets();
    for (int i = 0; i < bullets.size(); ) {
        bool bulletErased = false;

        for (int j = 0; j < enemies.size(); ++j) {
            if (CheckCollisionCircleRec(bullets[i].GetPosition(), 5, enemies[j].GetRect())) {
                bullets.erase(bullets.begin() + i);
                bulletErased = true;

                enemies[j].Damage();
                player.IncrementCoins(1);

                if (!enemies[j].IsAlive()) {
                    enemies.erase(enemies.begin() + j);
                }

                break;
            }
        }

        if (!bulletErased) {
            ++i;
        }
    }
}
