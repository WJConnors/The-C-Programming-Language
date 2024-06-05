#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    const int windowDimensions[2]{512, 380};
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    const int gravity{1000};


    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebData{
        {0.0f, 0.0f, (float)nebula.width/8, (float)nebula.height/8},
        {(float)windowDimensions[0], (float)windowDimensions[1] - nebula.height/8},
        0,
        1.0f/12.0f,
        0.0f
    };
    AnimData nebData2{
        {0.0f, 0.0f, (float)nebula.width/8, (float)nebula.height/8},
        {(float)windowDimensions[0] + 300, (float)windowDimensions[1] - nebula.height/8},
        0,
        1.0f/16.0f,
        0.0f
    };

    int nebVel{-200};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{
        {0.0f, 0.0f, (float)scarfy.width/6, (float)scarfy.height},
        {(float)windowDimensions[0]/2 - (scarfy.width/6)/2, (float)windowDimensions[1] - scarfy.height},
        0,
        1.0f / 12.0f,
        0.0f
    };

    bool isInAir{false};
    const int jumpVelocity{-600};
    int scarfyVel{0};    

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float dT = GetFrameTime();        

        BeginDrawing();
        ClearBackground(WHITE);        

        if(scarfyData.pos.y > windowDimensions[1] - scarfyData.rec.height)
        {
            scarfyVel = 0;
            isInAir = false;
        }
        else
        {
            scarfyVel += gravity * dT;
        }
        if(IsKeyDown(KEY_SPACE) && !isInAir)
        {
            scarfyVel += jumpVelocity;
            isInAir = true;
        }

        nebData.pos.x += nebVel * dT;
        scarfyData.pos.y += scarfyVel * dT;
        nebData2.pos.x += nebVel * dT;

        if (!isInAir)
        {
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {            
                scarfyData.runningTime = 0.0f;
                scarfyData.frame++;
                if(scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                } 
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;              
            }
        }        
        
        nebData.runningTime += dT;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0f;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if(nebData.frame > 7)
            {
                nebData.frame = 0;
            }            
        }

        nebData2.runningTime += dT;
        if (nebData2.runningTime >= nebData2.updateTime)
        {
            nebData2.runningTime = 0.0f;
            nebData2.rec.x = nebData2.frame * nebData2.rec.width;
            nebData2.frame++;
            if(nebData2.frame > 7)
            {
                nebData2.frame = 0;
            }            
        }

        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);            
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        DrawTextureRec(nebula, nebData2.rec, nebData2.pos, RED);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}