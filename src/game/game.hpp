#pragma once

#include "../player/player.hpp"
#include "raylib.h"
#include "vector"
#include "../enemy/enemy.hpp"

class Game {
public:
    Game(Player& playerRef);
    void Update();

private:
    Player& player;
    std::vector<Enemy> enemies;

    Rectangle testObject;
};
