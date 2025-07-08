#include <iostream>
#include <raylib.h>
#include "physics.hpp"
using namespace std;

int main()
{
    int width = 1920;
    int height = 1080;
    InitWindow(width, height, "engine");


    frame f;
    f.point1.x = 0;
    f.point1.y = 0;
    f.point2.x = 0;
    f.point2.y = height;
    f.point3.x = width;
    f.point3.y = height;
    f.point4.x = width;
    f.point4.y = 0;
    f.sideThick = 20;
    f.baseThick = 20;
    f.color = RAYWHITE;
    
    particle c;
    c.mass = 6; 
    c.centerX = 400;
    c.centerY = 200;
    c.radius = 20;
    
    int time = 0;
    SetTargetFPS(60);
    bool toggleGravity = 0;
    bool contact = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        drawFrame(f,0,0,0,height,width,height,width,0);
        control(c, f , width , height);
        gravity(c, f , width , height, toggleGravity);
        DrawCircle(c.centerX, c.centerY, c.radius, c.color);
        time = GetTime();
        DrawText(TextFormat("time: %i", time), 10, 10, 20, RAYWHITE);
        EndDrawing();
        
    }
    CloseWindow();
}