#include "raylib.h"
#include "../config/config.h"
#include "player/player.h"

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    int x = (SCREEN_WIDTH - 20) / 2;
    int y = (SCREEN_HEIGHT - 20) / 2;

    Player player = {x, y, PLAYER_SIZE, PLAYER_SPEED, playerColor};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        player.Update();

        
        BeginDrawing();
        ClearBackground(backgroundColor);

        player.Draw();

        DrawText("Hello, Raylib!", 20, 20, fontSize, textColor);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
