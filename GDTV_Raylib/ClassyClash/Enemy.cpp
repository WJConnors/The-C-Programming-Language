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
    if(!getAlive()) return;

    velocity = {Vector2Subtract(target->getScreenPos(), getScreenPos())};

    if (Vector2Length(velocity) < radius) velocity = {};

    BaseCharacter::tick(deltaTime);

    if(CheckCollisionRecs(getCollisionRec(), target->getCollisionRec()))
    {
        target->takeDamage(dps * deltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}