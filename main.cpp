#include <iostream>
#include <raylib.h>
#include "physics.h"
using namespace std;


int main()
{

    int width = 800;
    int height = 600;
    InitWindow(width, height, "engine");
    int time = 0;
    frame f;
    particle c;
    c.centerX = 400;
    c.centerY = 200;
    c.radius = 20;
    SetTargetFPS(60);
    bool toggleGravity = 0;
    Color d = RAYWHITE;
    int nframes = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        drawFrame(f);
        control(f, c.centerX, c.centerY);
        gravity(c, toggleGravity);
        DrawCircle(c.centerX, c.centerY, c.radius, c.color);
        time = GetTime();
        DrawText(TextFormat("time: %i", time), 10, 10, 20, RAYWHITE);
        EndDrawing();
        nframes++;
    }
    CloseWindow();
}