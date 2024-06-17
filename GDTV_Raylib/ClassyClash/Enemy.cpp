#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_Texture, Texture2D run_Texture)
{
    worldPos = pos;
    worldPos = pos;
    idle = idle_Texture;
    run = run_Texture;
    texture = idle;
    width = idle.width/maxFrames;
    height = idle.height;
    speed = 3.0f;
}

void Enemy::tick(float deltaTime)
{
    Vector2 toTarget{Vector2Subtract(target->getScreenPos(), screenPos)};
    toTarget = Vector2Normalize(toTarget);
    Vector2Scale(toTarget, speed);
    worldPos = Vector2Add(worldPos, toTarget);

    screenPos = Vector2Subtract(worldPos, target->getWorldPos());

    BaseCharacter::tick(deltaTime);
}
