#include "Character.h"
#include "raymath.h"

//Class Function pasted outside to add to the Character CLass Prototype
Character::Character(int winX, int winY)
{
    width = texture.width / maxFrames;
    height = texture.height;
    screenPos = {
        static_cast<float>(winX) / 2.0f - scale * (0.5f * width / 6.0f),
        static_cast<float>(winY) / 2.0f - scale * (0.5f * height),
    };
}

void Character::tick(float deltaTime)

{
    worldPosLastFrame = worldPos;
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        texture = texture_run;
    }
    else
    {
        texture = texture_idle;
    }

    //Character Animatio function

    //Update the idle frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0;
        frame++;
        if (frame > maxFrames)
            frame = 0;
    }

    //Update the knight facing direction
    direction.x < 0 ? rightLeft = -1.f : rightLeft = 1.f;

    //Drawing the character and player for the frame

    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, scale, WHITE);
};

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle Character::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale};
}