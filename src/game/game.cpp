#include "game.hpp"
#include "../../config/playerConfig.h"

Game::Game(Player& playerRef) : player(playerRef) {
    enemies.push_back(Enemy(100, 100, 30, 3, 1, RED));
    enemies.push_back(Enemy(200, 200, 20, 3, 1, BLACK));
}
void Game::Update() {
    player.Update();
    player.Draw();
    for (Enemy& enemy : enemies) {
        if(enemy.IsAlive()) {
            enemy.Draw();
            enemy.MoveTowardsPlayer(player.GetPosition());
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

                if (enemies[j].IsAlive()) {
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
