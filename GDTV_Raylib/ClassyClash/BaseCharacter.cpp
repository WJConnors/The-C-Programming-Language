#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{
    
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{screenPos.x, screenPos.y, scale * width, scale * height};
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0.0f;
        frame++;
        if (frame > maxFrames) frame = 0;
    }

    Rectangle source = {frame * width, 0.0f, rightLeft * width, height};
    Rectangle dest = {screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
}