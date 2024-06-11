#include "raylib.h"

int main()
{
    // Initialization
    const int screenWidth = 384;
    const int screenHeight = 384;
    InitWindow(screenWidth, screenHeight, "Classy Clash");

    Texture2D worldMap = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureEx(worldMap, {0, 0}, 0, 4, WHITE);

        EndDrawing();
    }
    UnloadTexture(worldMap);
    CloseWindow(); // Close window and OpenGL context
}