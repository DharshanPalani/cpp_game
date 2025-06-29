#include "raylib.h"
#include "../config/config.h"
#include "../config/playerConfig.h"
#include "player/player.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    int x = (SCREEN_WIDTH - PLAYER_SIZE) / 2;
    int y = (SCREEN_HEIGHT - PLAYER_SIZE) / 2;

    Player player(x, y, PLAYER_SIZE, PLAYER_SPEED, playerColor);

    Rectangle targetObject = {200, 200, 50, 50};

    while (!WindowShouldClose()) {
        player.Update();

        // Check bullet collisions with object
        auto& bullets = player.GetBullets();
        for (int i = 0; i < bullets.size(); i++) {
            if (CheckCollisionCircleRec(bullets[i].GetPosition(), 5, targetObject)) {
                bullets.erase(bullets.begin() + i);
                i--;
            }
        }

        BeginDrawing();
        ClearBackground(backgroundColor);

        player.Draw();
        DrawRectangleLinesEx(targetObject, 3, RED);
        player.DrawHitBox(CheckCollisionRecs(player.GetRect(), targetObject));

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
