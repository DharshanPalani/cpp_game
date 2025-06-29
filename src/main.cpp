#include "raylib.h"
#include "../config/config.h"
#include "../config/playerConfig.h"
#include "player/player.hpp"
#include "game/game.hpp"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    int x = (SCREEN_WIDTH - PLAYER_SIZE) / 2;
    int y = (SCREEN_HEIGHT - PLAYER_SIZE) / 2;

    Player player(x, y, PLAYER_SIZE, PLAYER_SPEED, playerColor);

    Game game(player);

    Rectangle targetObject = {200, 200, 50, 50};

    while (!WindowShouldClose()) {
        // player.Update();
        BeginDrawing();
        ClearBackground(backgroundColor);
        game.Update();
        DrawRectangleLinesEx(targetObject, 3, RED);
        DrawText(player.GetBulletCount().c_str(), 10, 10, 20, BLACK);
        player.DrawHitBox(CheckCollisionRecs(player.GetRect(), targetObject));

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
