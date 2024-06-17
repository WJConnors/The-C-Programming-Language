#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
    
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    if (Vector2Length(velocity) != 0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        rightLeft = velocity.x < 0.0f ? -1.0f : 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0.0f;
        frame++;
        if (frame > maxFrames) frame = 0;
    }

    Rectangle source = {frame * width, 0.0f, rightLeft * width, height};
    Rectangle dest = {getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
}