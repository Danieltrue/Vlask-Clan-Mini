#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    //Window Dimension
    int winX = 348;
    int winY = 348;
    const float mapScale{4.f};

    //Create the window
    InitWindow(winX, winY, "Vlask Clan Mini");

    //load the map
    Texture2D map = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    //
    Character knight{winX, winY};

    Enemy goblin{Vector2{},
                 LoadTexture("./characters/goblin_idle_spritesheet.png"),
                 LoadTexture("./characters/goblin_run_spritesheet.png")};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("./nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("./nature_tileset/Log.png")},
    };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        //Draw the map on the screen
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        knight.tick(GetFrameTime());

        //Draw the prop on the screen [TREE,STONE,ROCK,LEAVE,BUSH AND ....]
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        };
        //Check to see if character is not passing the bound
        if (knight.getWorldPos().x < 0 ||
            knight.getWorldPos().y < 0 ||
            knight.getWorldPos().x + winX > map.width * mapScale ||
            knight.getWorldPos().y > winY * map.height * mapScale)
        {
            //...
            knight.undoMovement();
        };

        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {

                knight.undoMovement();
            }
        }
        //call the enemy to the screen
        goblin.tick(GetFrameTime());
        //End the Drawing
        EndDrawing();
    }
    CloseWindow();
    // UnloadTexture(map);
}