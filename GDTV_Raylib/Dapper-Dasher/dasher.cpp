#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimDate(AnimData data, float deltaTime, int maxFrame)
{
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0f;
        data.rec.x = data.frame * data.rec.width;     
        data.frame++;
        if(data.frame > maxFrame)
        {
            data.frame = 0;
        }                 
    }
    return data;
}

int main()
{
    const int windowDimensions[2]{512, 380};
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    const int gravity{1000};


    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    const int sizeOfNebulae{3};
    AnimData nebulae[sizeOfNebulae]{};
    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0f;
        nebulae[i].rec.y = 0.0f;
        nebulae[i].rec.width = (float)nebula.width/8;
        nebulae[i].rec.height = (float)nebula.height/8;
        nebulae[i].pos.x = (float)windowDimensions[0] + i * 300;
        nebulae[i].pos.y = (float)windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].updateTime = 1.0f/12.0f;
        nebulae[i].runningTime = 0.0f;
    }

    int nebVel{-200};

    float finishLine{nebulae[sizeOfNebulae - 1].pos.x};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");

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

    float bgX{0.0f};
    float mgX{0.0f};
    float fgX{0.0f};

    bool collision{false};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        float dT = GetFrameTime();        

        BeginDrawing();
        ClearBackground(WHITE);  

        bgX -= 20.0f * dT;
        if (bgX <= -background.width * 2.0f)
        {
            bgX = 0.0f;
        }
        Vector2 bg1Pos{bgX, 0.0f};
        DrawTextureEx(background, bg1Pos, 0.0f, 2.0f, WHITE);      
        Vector2 bg2Pos{bgX + background.width * 2.0f, 0.0f};
        DrawTextureEx(background, bg2Pos, 0.0f, 2.0f, WHITE);

        mgX -= 40.0f * dT;
        if (mgX <= -midground.width * 2.0f)
        {
            mgX = 0.0f;
        }
        Vector2 mg1Pos{mgX, 0.0f};
        DrawTextureEx(midground, mg1Pos, 0.0f, 2.0f, WHITE);
        Vector2 mg2Pos{mgX + midground.width * 2.0f, 0.0f};
        DrawTextureEx(midground, mg2Pos, 0.0f, 2.0f, WHITE);

        fgX -= 80.0f * dT;
        if (fgX <= -foreground.width * 2.0f)
        {
            fgX = 0.0f;
        }
        Vector2 fg1Pos{fgX, 0.0f};
        DrawTextureEx(foreground, fg1Pos, 0.0f, 2.0f, WHITE);
        Vector2 fg2Pos{fgX + foreground.width * 2.0f, 0.0f};
        DrawTextureEx(foreground, fg2Pos, 0.0f, 2.0f, WHITE);

        if(isOnGround(scarfyData, windowDimensions[1]))
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

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebVel * dT;   
        }
        finishLine += nebVel * dT;

        scarfyData.pos.y += scarfyVel * dT;

        if (!isInAir)
        {
            scarfyData = updateAnimDate(scarfyData, dT, 5);
        }   

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimDate(nebulae[i], dT, 7);
        }  

        for (AnimData nebula : nebulae)
        {
            float pad{50.0f};
            Rectangle nebRec{nebula.pos.x + pad, nebula.pos.y + pad, nebula.rec.width - 2 * pad, nebula.rec.height - 2 * pad};
            Rectangle scarfyRec{scarfyData.pos.x, scarfyData.pos.y, scarfyData.rec.width, scarfyData.rec.height};
            if(CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }   

        if (collision)
        {
            DrawText("Game Over!", 165, 180, 40, RED);
        }
        else if (finishLine <= 0)
        {
            DrawText("You Win!", 165, 180, 40, RED);
        }
        else
        {
            for (int i = 0; i < sizeOfNebulae; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);  
            }        
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);            
        }   
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}