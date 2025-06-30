#pragma once

#include "../player/player.hpp"
#include "raylib.h"
#include "vector"
#include "../enemy/enemy.hpp"
#include "../camera/camera.hpp"

class Game {
public:
    Game(Player& playerRef);
    void Update(CameraShake& shake, Camera2D* camera);

    float damageCooldown = 0.0f;
    const float DAMAGE_DELAY = 2.0f;


private:
    Player& player;
    std::vector<Enemy> enemies;

    Rectangle testObject;
};
