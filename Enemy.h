#include "raylib.h"

class Enemy
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();

private:
    Texture2D texture{LoadTexture("./characters/knight_idle_spritesheet.png")};
    Texture2D texture_idle{LoadTexture("./characters/knight_idle_spritesheet.png")};
    Texture2D texture_run{LoadTexture("./characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    float rightLeft{1.0};
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
    const float speed{4.0};
    float height{};
    float width{};
    float scale{4.f};
};