#include <iostream>
#include <raylib.h>
using namespace std;
struct frame
{
    Vector2 point1;
    Vector2 point2;
    Vector2 point3;
    Vector2 point4;
    int sideThick;
    int baseThick;
    Color color;
};
struct circle
{
    int centerx;
    int centery;
    int radius;
    Color color;
};

void drawFrame(frame f ,
               int point1x = 0 , 
               int point1y = 0 ,
               int point2x = 0 ,
               int point2y = 600 ,
               int point3x = 800 ,
               int point3y = 600 ,
               int point4x = 800 ,
               int point4y = 0 ,
               int sideThick = 20 ,
               int baseThick = 25 ,
               Color color = RAYWHITE)
{
    f.point1.x = point1x ;
    f.point1.y = point1y ;
    f.point2.x = point2x ;
    f.point2.y = point2y ;
    f.point3.x = point3x ;
    f.point3.y = point3y ;
    f.point4.x = point4x ;
    f.point4.y = point4y ;
    f.sideThick = sideThick ;
    f.baseThick = baseThick ;
    f.color = color;

    DrawLineEx(f.point1 , f.point2 , f.sideThick , f.color);
    DrawLineEx(f.point2 , f.point3 , f.sideThick , f.color);
    DrawLineEx(f.point3 , f.point4 , f.baseThick , f.color);
}

void control(frame f, int &initx , int &inity)
{
    if (IsKeyDown(KEY_UP) && inity >= 25)
        inity -= 10;
    else if (IsKeyDown(KEY_DOWN) && inity <= 600-30-10)
        inity += 10;
    else if (IsKeyDown(KEY_RIGHT) && initx <= 800-25-10)
        initx += 10;
    else if (IsKeyDown(KEY_LEFT) && initx >=25+10)
        initx -= 10;
}

int main()
{
    int width = 800;
    int height = 600;
    frame f;
    InitWindow(width, height, "engine");
    SetTargetFPS(60);
    
    int initialx=400;
    int initialy=300;
    Color d = RAYWHITE;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        control(f , initialx , initialy);
        drawFrame(f);
        DrawCircle(initialx ,initialy ,20 , RAYWHITE);
        EndDrawing();
        

    }
    CloseWindow();
}