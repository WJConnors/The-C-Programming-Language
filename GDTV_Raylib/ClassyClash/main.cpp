#include "raylib.h"
#include "raymath.h"

class Character
{
    private:
        Texture2D texture{(LoadTexture("characters/knight_idle_spritesheet.png"))};
        Texture2D idle{(LoadTexture("characters/knight_idle_spritesheet.png"))};
        Texture2D run{(LoadTexture("characters/knight_run_spritesheet.png"))};
        Vector2 screenPos{0.0f, 0.0f};
        Vector2 worldPos{0.0f, 0.0f};

        float rightLeft{1.0f};
        float runningTime{0.0f};
        int frame{0};
        const int maxFrames{6};
        const float updateTime{1.0f/12.0f};

        const float speed{4.0f};


    public:
        Vector2 getWorldPos() { return worldPos; }
        void setScreenPos(Vector2 pos);
        void tick(float deltaTime);
};

void Character::setScreenPos(Vector2 window)
{
    screenPos = {(float)window.x / 2.0f -  4.0f * (0.5f * (float)texture.width/6), (float)window.y / 2.0f - 4.0f * (0.5f * (float)texture.height)};
}

void Character::tick(float deltaTime)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x -= 1;
    if (IsKeyDown(KEY_D)) direction.x += 1;
    if (IsKeyDown(KEY_W)) direction.y -= 1;
    if (IsKeyDown(KEY_S)) direction.y += 1;
    if (Vector2Length(direction) != 0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        rightLeft = direction.x < 0.0f ? -1.0f : 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0.0f;
        frame++;
        if (frame > maxFrames) frame = 0;
    }

    Rectangle source = {frame * (float)texture.width/6, 0.0f, rightLeft * (float)texture.width/6, (float)texture.height};
    Rectangle dest = {screenPos.x, screenPos.y, 4.0f * (float)texture.width/6, 4.0f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
}

int main()
{
    // Initialization
    const int screenWidth = 384;
    const int screenHeight = 384;
    InitWindow(screenWidth, screenHeight, "Classy Clash");

    Texture2D worldMap = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight;
    knight.setScreenPos({screenWidth, screenHeight});

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(WHITE);        

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        DrawTextureEx(worldMap, mapPos, 0, 4, WHITE);

        knight.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(worldMap);
    CloseWindow(); // Close window and OpenGL context
}