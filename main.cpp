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
    int centerX = 0;
    int centerY = 0;
    int radius = 5;
    double velcoity = 0;
    bool direction = 1;
    Color color = RAYWHITE;
};

void drawFrame(frame f,
               int point1x = 0,
               int point1y = 0,
               int point2x = 0,
               int point2y = 600,
               int point3x = 800,
               int point3y = 600,
               int point4x = 800,
               int point4y = 0,
               int sideThick = 20,
               int baseThick = 25,
               Color color = RAYWHITE)
{
    f.point1.x = point1x;
    f.point1.y = point1y;
    f.point2.x = point2x;
    f.point2.y = point2y;
    f.point3.x = point3x;
    f.point3.y = point3y;
    f.point4.x = point4x;
    f.point4.y = point4y;
    f.sideThick = sideThick;
    f.baseThick = baseThick;
    f.color = color;

    DrawLineEx(f.point1, f.point2, f.sideThick, f.color);
    DrawLineEx(f.point2, f.point3, f.sideThick, f.color);
    DrawLineEx(f.point3, f.point4, f.baseThick, f.color);
}

void control(frame f, int &x, int &y)

{
    if (IsKeyDown(KEY_UP) && y >= 25)
        y -= 10;
    else if (IsKeyDown(KEY_DOWN) && y <= 600 - 30 - 10)
        y += 10;
    else if (IsKeyDown(KEY_RIGHT) && x <= 800 - 25 - 10)
        x += 10;
    else if (IsKeyDown(KEY_LEFT) && x >= 25 + 10)
        x -= 10;
}

void gravity(circle &c, bool &toggleGravity)

{   
    const float g = 980.0;
    const float restitution  = 0.7;
    
    cout << c.velcoity << endl ;
    if (IsKeyPressed(KEY_SPACE))
    {
        toggleGravity = !toggleGravity;
        c.velcoity = 0;
    }

    if (!toggleGravity) return;
    
        double deltaTime = GetFrameTime() ;
        
        c.velcoity += g * deltaTime;
        c.centerY += c.velcoity * deltaTime;
        
       
        if (c.centerY > 600 - c.radius - 10)
        {
            c.centerY = 600 - c.radius - 10;
            c.velcoity = -restitution * c.velcoity;
        }
    
}


int main()
{

    int width = 800;
    int height = 600;
    InitWindow(width, height, "engine");
    int time = 0;
    frame f;
    circle c;
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
        gravity(c , toggleGravity);
        DrawCircle(c.centerX, c.centerY, c.radius, c.color);
        time = GetTime();
        DrawText(TextFormat("time: %i",time), 10 ,10 , 20 , RAYWHITE);
        EndDrawing();
        nframes++;
    }
    CloseWindow();
}