#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) :
    screenWidth{winWidth},
    screenHeight{winHeight}
{
    width = texture.width/maxFrames;
    height = texture.height;
}

void Character::tick(float deltaTime)
{  
    if (!getAlive()) return;

    if (IsKeyDown(KEY_A)) velocity.x -= 1;
    if (IsKeyDown(KEY_D)) velocity.x += 1;
    if (IsKeyDown(KEY_W)) velocity.y -= 1;
    if (IsKeyDown(KEY_S)) velocity.y += 1;

    BaseCharacter::tick(deltaTime);  

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.0f)
    {
        origin = {0.0f, weapon.height * scale};
        offset = {35.0f, 55.0f};
        weaponRec = {getScreenPos().x + offset.x, getScreenPos().y + offset.y - weapon.height * scale, weapon.width * scale, weapon.height * scale};
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.0f : rotation = 0.0f;
    } 
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.0f, 55.0f};
        weaponRec = {getScreenPos().x + offset.x - weapon.width * scale, getScreenPos().y + offset.y - weapon.height * scale, weapon.width * scale, weapon.height * scale};
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.0f : rotation = 0.0f;
    }

    Rectangle source{0.0f, 0.0f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
}

Vector2 Character::getScreenPos()
{
    return Vector2{screenWidth / 2.0f -  scale * (0.5f * width), screenHeight / 2.0f - scale * (0.5f * height)};
}


void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.0f) setAlive(false);
}