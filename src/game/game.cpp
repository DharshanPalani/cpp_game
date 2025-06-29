#include "game.hpp"
#include "../../config/playerConfig.h"

Game::Game(Player& playerRef)
    : player(playerRef), testObject({200, 200, 50, 50}) {}

void Game::Update() {
    player.Update();
    player.Draw();

    auto& bullets = player.GetBullets();
    for (int i = 0; i < bullets.size(); ++i) {
        if (CheckCollisionCircleRec(bullets[i].GetPosition(), 5, testObject)) {
            bullets.erase(bullets.begin() + i);
            --i;
        }
    }
}
