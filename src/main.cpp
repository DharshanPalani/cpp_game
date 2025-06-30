#include "raylib.h"
#include "../config/config.h"
#include "../config/playerConfig.h"
#include "player/player.hpp"
#include "game/game.hpp"

// Game state enum
enum class GameState {
    MENU,
    PLAYING,
    SHOP,
    DEAD
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    
    // Center the player on screen
    int x = 300;
    int y = 300;
    
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

        if(state != GameState::MENU && state != GameState::DEAD) {
            DrawText(player.GetBulletCount().c_str(), 10, 10, 20, BLACK);
            DrawText(player.GetCoinCount().c_str(), 10, 30, 20, BLACK);
            DrawText(player.GetHealth().c_str(), 10, 50, 20, BLACK);
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
            
            if(IsKeyPressed(KEY_E)) {
                state = GameState::SHOP;
            }
            if(player.IsAlive() == false) {
                state = GameState::DEAD;
            }
        } else if (state == GameState::SHOP) {
            DrawRectangle(200, 150, 400, 300, DARKGRAY);
            DrawText("SHOP", 360, 200, 30, WHITE);

            DrawRectangle(250, 275, 300, 40, LIGHTGRAY);
            DrawText("Buy Health (+20) - 100 Coins", 255, 285, 20, BLACK);

            DrawRectangle(250, 325, 300, 40, LIGHTGRAY);
            DrawText("Buy Ammo (+3) - 1 Coins", 255, 335, 20, BLACK);

            DrawRectangle(250, 375, 300, 40, LIGHTGRAY);
            DrawText("Return to Game", 255, 385, 20, BLACK);

            Vector2 mouse = GetMousePosition();

            if (CheckCollisionPointRec(mouse, {250, 275, 300, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                player.IncrementHealth();
            }

            if (CheckCollisionPointRec(mouse, {250, 325, 300, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                player.IncrementAmmo();
            }

            if (CheckCollisionPointRec(mouse, {250, 375, 300, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                state = GameState::PLAYING;
            }
        } else if(state == GameState::DEAD) {
            std::string msg = "YOU ARE DEAD";
            std::string msg2 = "PRESS P TO PLAY";
            int fontSize = 30;
            int fontSize2 = 20;
            int textWidth = MeasureText(msg.c_str(), fontSize);
            int textWidth2 = MeasureText(msg2.c_str(), fontSize2);
            int x = (SCREEN_WIDTH - textWidth) / 2;
            int y = (SCREEN_HEIGHT - textWidth) / 2;
            int x2 = (SCREEN_WIDTH - textWidth2) / 2;
            int y2 = (SCREEN_HEIGHT - textWidth2) / 2;
            DrawText(msg.c_str(), x, y, fontSize, WHITE);
            DrawText(msg2.c_str(), x2, y2 + 20, fontSize2, BLACK);
            if(IsKeyPressed(KEY_P)) {
                state = GameState::PLAYING;
                game.Reset();
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
