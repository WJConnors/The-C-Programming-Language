#include "raylib.h"

class Prop
{
    private:
        Vector2 worldPos{0.0f, 0.0f};
        Texture2D texture{};        
        float scale{4.0f};

    public:
        Prop(Vector2 pos, Texture2D tex);
        void Render(Vector2 knightPos) const;
        Rectangle getCollisionRec (Vector2 knightPos) const;
};