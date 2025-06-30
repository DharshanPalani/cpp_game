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

private:
    Player& player;
    std::vector<Enemy> enemies;

    Rectangle testObject;
};
