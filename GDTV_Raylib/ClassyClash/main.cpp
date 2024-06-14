#include "raylib.h"
#include "raymath.h"

int main()
{
    // Initialization
    const int screenWidth = 384;
    const int screenHeight = 384;
    InitWindow(screenWidth, screenHeight, "Classy Clash");

    Texture2D worldMap = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    float speed{4.0f};

    Texture2D knightIdle = (LoadTexture("characters/knight_idle_spritesheet.png"));
    Texture2D knightRun = (LoadTexture("characters/knight_run_spritesheet.png"));
    Texture2D curAnimation = knightIdle;
    Vector2 knightPos{(float)screenWidth / 2.0f -  4.0f * (0.5f * (float)knightIdle.width/6), (float)screenHeight / 2.0f - 4.0f * (0.5f * (float)knightIdle.height)};

    float rightLeft{1.0f};
    float runningTime{0.0f};
    int frame{0};
    const int maxFrames{6};
    const float updateTime{1.0f/12.0f};

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(WHITE);        

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1;
        if (IsKeyDown(KEY_D)) direction.x += 1;
        if (IsKeyDown(KEY_W)) direction.y -= 1;
        if (IsKeyDown(KEY_S)) direction.y += 1;
        if (Vector2Length(direction) != 0)
        {
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            rightLeft = direction.x < 0.0f ? -1.0f : 1.0f;
            curAnimation = knightRun;
        }
        else
        {
            curAnimation = knightIdle;
        }

        DrawTextureEx(worldMap, mapPos, 0, 4, WHITE);

        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            runningTime = 0.0f;
            frame++;
            if (frame > maxFrames) frame = 0;
        }

        Rectangle source = {frame * (float)curAnimation.width/6, 0.0f, rightLeft * (float)curAnimation.width/6, (float)curAnimation.height};
        Rectangle dest = {knightPos.x, knightPos.y, 4.0f * (float)curAnimation.width/6, 4.0f * (float)curAnimation.height};
        DrawTexturePro(curAnimation, source, dest, Vector2{0.0f, 0.0f}, 0.0f, WHITE);

        EndDrawing();
    }
    UnloadTexture(worldMap);
    CloseWindow(); // Close window and OpenGL context
}