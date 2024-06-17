#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    // Initialization
    const int screenWidth = 384;
    const int screenHeight = 384;
    InitWindow(screenWidth, screenHeight, "Classy Clash");

    Texture2D worldMap = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale = 4.0f;

    Character knight{screenWidth, screenHeight};

    Enemy enemies[]{
        Enemy{Vector2{500.0f, 500.0f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")},
        Enemy{Vector2{200.0f, 200.0f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")}
    };    
    for (Enemy& enemy : enemies)
    {
        enemy.setTarget(&knight);
    }

    Prop props[]{
        Prop{Vector2{200, 500}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{500, 200}, LoadTexture("nature_tileset/Log.png")}
    };

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(WHITE);        

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);
        
        DrawTextureEx(worldMap, mapPos, 0, mapScale, WHITE);

        for (const Prop& prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive())
        {
            DrawText("Game Over", 55.5f, 45.5f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string health = "Health: ";
            health.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(health.c_str(), 55.5f, 45.5f, 40, RED);
        }

        knight.tick(GetFrameTime());
        

        if (knight.getWorldPos().x < 0.0f ||
            knight.getWorldPos().y < 0.0f ||
            knight.getWorldPos().x + screenWidth >  worldMap.width * mapScale||
            knight.getWorldPos().y + screenHeight > worldMap.height * mapScale)
        {
            knight.undoMovement();
        }
        for (const Prop& prop : props)
        {
            if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos())))
            {
                knight.undoMovement();
            }
        }
        
        for (Enemy& enemy : enemies)
        {
            enemy.tick(GetFrameTime());
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && knight.getAlive())
        {
            for (Enemy& enemy : enemies)
            {
                if (CheckCollisionRecs(knight.getWeaponRec(), enemy.getCollisionRec()))
                {
                    enemy.setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    UnloadTexture(worldMap);
    CloseWindow(); // Close window and OpenGL context
}