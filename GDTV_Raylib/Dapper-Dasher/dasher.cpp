#include "raylib.h"

int main()
{
    const int windowWidth{512};
    const int windowHeight{380};
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    const int gravity{1000};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec = {.x = 0, .y = 0, .width = (float)scarfy.width / 6, .height = (float)scarfy.height};
    Vector2 scarfyPos = {.x = windowWidth/2 - scarfyRec.width/2, .y = windowHeight - scarfyRec.height};

    int frame{0};
    const float updateTime = 1.0/12.0;
    float runningTime{0};

    bool isInAir{false};
    const int jumpVelocity{-600};
    int velocity{0};    

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float dT = GetFrameTime();        

        BeginDrawing();
        ClearBackground(WHITE);        

        if(scarfyPos.y > windowHeight - scarfyRec.height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity * dT;
        }
        if(IsKeyDown(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
            isInAir = true;
        }
        scarfyPos.y += velocity * dT;

        runningTime += dT;
        
        if (runningTime >= updateTime)
        {            
            runningTime = 0;
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if(frame > 5)
            {
            frame = 0;
            }               
        }
             

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}