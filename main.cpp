#include "raylib.h"
#include "raymath.h"

class Character {
    public:
        Vector2 getWorldPos() { return worldPos; }
    private:
        Texture2D texture;
        Texture2D texture_idle;
        Texture2D texture_run;
        Vector2 screenPos;
        Vector2 worldPos;
        float rightLeft{1.0};
        float runningTime{};
        const int frame{};
        const int maxFrames{6};
        const float updateTime{1.f / 12.f};
};

int main() {
    //Window Dimension
    int winX = 348;
    int winY = 348;

    //Create the window
    InitWindow(winX,winY,"Vlask Clan Mini");

    //load the map
    Texture2D map = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0,0.0};
    float speed{4.0};

    Texture2D knight = LoadTexture("./characters/knight_idle_spritesheet.png");
    Texture2D knight_idle = LoadTexture("./characters/knight_idle_spritesheet.png");
    Texture2D knight_Run = LoadTexture("./characters/knight_run_spritesheet.png");


    Vector2 knightPos {
        (float)winX / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
        (float)winY / 2.0f - 4.0f * (0.5f * (float)knight.height),
    };

    //Knight Variables
    float rightLeft{1.f};
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;

        if (Vector2Length(direction) != 0.0)
        {
            mapPos = Vector2Subtract(mapPos,Vector2Scale( Vector2Normalize(direction), speed));
            knight = knight_Run;
        } else {
            knight = knight_idle;
        }


        //Update the idle frame
        runningTime += GetFrameTime();
        if(runningTime >= updateTime) {
            runningTime = 0;
            frame++;
            if(frame > maxFrames) frame = 0;
        }
        //Update the knight facing direction
        direction.x < 0 ? rightLeft = -1.f : rightLeft = 1.f;

        //Draw the map on the screen
        DrawTextureEx(map,mapPos,0.0,4.0,WHITE);
        Rectangle source {frame * (float)knight.width / 6.f,0.f,rightLeft * (float)knight.width / 6.f,(float)knight.height};
        Rectangle dest {knightPos.x,knightPos.y,4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};

        DrawTexturePro(knight,source,dest,Vector2{},4.0f,WHITE);

        //End the Drawing
        EndDrawing();
    }
    CloseWindow();
    // UnloadTexture(map);
}