#include "raylib.h"
#include "../config/config.h"
#include "../config/playerConfig.h"
#include "player/player.hpp"
#include "game/game.hpp"

// Game state enum
enum class GameState {
    MENU,
    PLAYING
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Center the player on screen
    int x = (SCREEN_WIDTH - PLAYER_SIZE) / 2;
    int y = (SCREEN_HEIGHT - PLAYER_SIZE) / 2;

    Player player(x, y, PLAYER_SIZE, PLAYER_SPEED, playerColor);
    Game game(player);

    GameState state = GameState::MENU;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(backgroundColor);
        
        if (state == GameState::MENU) {
            ClearBackground(BLACK);
            int titleFontSize = 40;
            int optionFontSize = 20;

            const char* titleText = "Shoot the kids";
            int titleWidth = MeasureText(titleText, titleFontSize);
            DrawText(titleText, (SCREEN_WIDTH - titleWidth) / 2, 100, titleFontSize, WHITE);

            const char* startText = "Press ENTER to Start";
            int startWidth = MeasureText(startText, optionFontSize);
            DrawText(startText, (SCREEN_WIDTH - startWidth) / 2, 200, optionFontSize, LIGHTGRAY);

            const char* quitText = "Press ESC to Quit";
            int quitWidth = MeasureText(quitText, optionFontSize);
            DrawText(quitText, (SCREEN_WIDTH - quitWidth) / 2, 240, optionFontSize, LIGHTGRAY);


            if (IsKeyPressed(KEY_ENTER)) {
                state = GameState::PLAYING;
            } else if (IsKeyPressed(KEY_ESCAPE)) {
                break;
            }

        } else if (state == GameState::PLAYING) {
            game.Update();

            DrawText(player.GetBulletCount().c_str(), 10, 10, 20, BLACK);
            DrawText(player.GetCoinCount().c_str(), 30, 30, 20, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
