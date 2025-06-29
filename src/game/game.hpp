#pragma once

#include "../player/player.hpp"
#include "raylib.h"

class Game {
public:
    Game(Player& playerRef);
    void Update();

private:
    Player& player;
    Rectangle testObject;
};
