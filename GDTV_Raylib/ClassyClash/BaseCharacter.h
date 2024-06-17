#include "raylib.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter
{
    protected:
        Texture2D texture{(LoadTexture("characters/knight_idle_spritesheet.png"))};
        Texture2D idle{(LoadTexture("characters/knight_idle_spritesheet.png"))};
        Texture2D run{(LoadTexture("characters/knight_run_spritesheet.png"))};
        Vector2 screenPos{0.0f, 0.0f};
        Vector2 worldPos{0.0f, 0.0f};
        Vector2 worldPosLastFrame{0.0f, 0.0f};
        float width{};
        float height{};

        float rightLeft{1.0f};
        float runningTime{0.0f};
        int frame{0};
        int maxFrames{6};
        float updateTime{1.0f/12.0f};

        float speed{4.0f};
        float scale{4.0f};

    public:
        BaseCharacter();
        Vector2 getWorldPos() { return worldPos; }
        void undoMovement() { worldPos = worldPosLastFrame; }
        Rectangle getCollisionRec();
        virtual void tick(float deltaTime);
};

#endif