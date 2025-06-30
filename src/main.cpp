#include "raylib.h"
#include "../config/config.h"
#include "../config/playerConfig.h"
#include "player/player.hpp"
#include "game/game.hpp"

// Game state enum
enum class GameState {
    MENU,
    PLAYING,
    SHOP
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    
    // Center the player on screen
    int x = (SCREEN_WIDTH - PLAYER_SIZE) / 2;
    int y = (SCREEN_HEIGHT - PLAYER_SIZE) / 2;
    
    Camera2D camera = { 0 };
    camera.target = { 0.0f, 0.0f };
    camera.zoom = 1.0f;
    
    Player player(x, y, PLAYER_SIZE, PLAYER_SPEED, playerColor);
    Game game(player);
    CameraShake cameraShake;

    GameState state = GameState::MENU;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(backgroundColor);

        if(state != GameState::MENU) {
            DrawText(player.GetBulletCount().c_str(), 10, 10, 20, BLACK);
            DrawText(player.GetCoinCount().c_str(), 10, 30, 20, BLACK);
        }
        
        if (state == GameState::MENU) {
            ClearBackground(BLACK);
            int titleFontSize = 40;
            int optionFontSize = 20;

            const char* titleText = "Shoot With Gun";
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
            } else if(IsKeyPressed(KEY_E)) {
                state = GameState::SHOP;
            }

        } else if (state == GameState::PLAYING) {
            BeginMode2D(camera);
            game.Update(cameraShake, &camera);
            // DrawText(player.GetBulletCount().c_str(), 10, 10, 20, BLACK);
            // DrawText(player.GetCoinCount().c_str(), 10, 30, 20, BLACK);
            
            if(IsKeyPressed(KEY_E)) {
                state = GameState::SHOP;
            }
        } else if (state == GameState::SHOP) {
            DrawRectangle(100, 100, 400, 300, DARKGRAY);
            DrawText("SHOP", 250, 120, 30, WHITE);

            DrawRectangle(150, 170, 300, 40, LIGHTGRAY);
            DrawText("Buy Health (+20) - 100 Coins", 160, 180, 20, BLACK);

            DrawRectangle(150, 230, 300, 40, LIGHTGRAY);
            DrawText("Buy Ammo (+10) - 50 Coins", 160, 240, 20, BLACK);

            DrawRectangle(150, 290, 300, 40, LIGHTGRAY);
            DrawText("Return to Game", 160, 300, 20, BLACK);

            Vector2 mouse = GetMousePosition();

            if (CheckCollisionPointRec(mouse, {150, 170, 300, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // if (player.GetCoinValue() >= 100) {
                //     player.AddHealth(20);
                //     player.SpendCoins(100);
                // }
            }

            if (CheckCollisionPointRec(mouse, {150, 230, 300, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // if (player.GetCoinValue() >= 50) {
                //     player.AddAmmo(10);
                //     player.SpendCoins(50);
                // }
            }

            if (CheckCollisionPointRec(mouse, {150, 290, 300, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                state = GameState::PLAYING;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
