#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
    private:
        int screenWidth{};
        int screenHeight{};
        Texture2D weapon{(LoadTexture("characters/weapon_sword.png"))};
        Rectangle weaponRec{};
        float health{100.0f};
    public:
        Character(int screenWidth, int screenHeight);
        virtual void tick(float deltaTime) override;
        virtual Vector2 getScreenPos() override;
        Rectangle getWeaponRec() { return weaponRec; }
        float getHealth() const { return health; }
        void takeDamage(float damage);
};

#endif