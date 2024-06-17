#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    width = (float)texture.width/maxFrames;
    height = (float)texture.height;

    screenPos = {winWidth / 2.0f -  scale * (0.5f * width), winHeight / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);

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
}

