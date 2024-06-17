#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
    private:
        Character* target{nullptr};
    public:
        Enemy(Vector2 pos, Texture2D idle_Texture, Texture2D run_Texture);
        virtual void tick(float deltaTime) override;
        void setTarget(Character* knight) { target = knight; }
};