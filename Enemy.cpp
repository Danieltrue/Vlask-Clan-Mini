#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
    : worldPos(pos),
      texture(idle_texture),
      texture_idle(idle_texture),
      texture_run(run_texture)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

void Enemy::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    //Update the idle frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0;
        frame++;
        if (frame > maxFrames)
            frame = 0;
    }

    //Drawing the character and player for the frame

    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, scale, WHITE);
}

void Enemy::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle Enemy::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale};
}
