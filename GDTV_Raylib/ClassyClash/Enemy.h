#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
    private:
        Character* target{nullptr};
        float dps {10.0f};
        float radius{25.0f};
    public:
        Enemy(Vector2 pos, Texture2D idle_Texture, Texture2D run_Texture);
        virtual void tick(float deltaTime) override;
        void setTarget(Character* knight) { target = knight; }
        virtual Vector2 getScreenPos() override;
};