#include "game.hpp"
#include "../../config/playerConfig.h"

Game::Game(Player& playerRef) : player(playerRef) {
    enemies.push_back(Enemy(100, 100, 30, 3, RED));
    enemies.push_back(Enemy(200, 200, 20, 3, BLACK));

}
void Game::Update() {
    player.Update();
    player.Draw();
    for (Enemy& enemy : enemies) {
        enemy.Draw();
    }

    auto& bullets = player.GetBullets();
    for (int i = 0; i < bullets.size(); ) {
        bool erased = false;

        for (Enemy& enemy : enemies) {
            if (CheckCollisionCircleRec(bullets[i].GetPosition(), 5, enemy.GetRect())) {
                bullets.erase(bullets.begin() + i);
                erased = true;
                break;
            }
        }

        if (!erased) {
            ++i;
        }
}

}
