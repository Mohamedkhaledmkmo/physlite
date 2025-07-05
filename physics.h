#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>
#include <cmath>

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

struct particle
{
    int centerX = 0;
    int centerY = 0;
    int radius = 5;
    float mass = 1;
    double velcoityH = 0;
    double velcoityV = 0;
    Color color = RAYWHITE;
};

void drawFrame(frame f,
               float point1x = 0,
               float point1y = 0,
               float point2x = 0,
               float point2y = 600,
               float point3x = 800,
               float point3y = 600,
               float point4x = 800,
               float point4y = 0,
               float sideThick = 20,
               float baseThick = 25,
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



void horizontalForce(particle &c)
{
    float f = 90;
    float a = f / c.mass;
    float dt = GetFrameTime();
    c.velcoityH += a * dt;
    c.centerX += c.velcoityH * dt;
}

void impulse(particle &c)
{
    int j = 980;
    c.velcoityH += j / c.mass;
}

Vector2 dragForce(particle &c)
{
    Vector2 dragForce;
    const float airDensity = 1.2;
    const float dragCoefficient = 0.47;
    float radius_m = c.radius * 0.01 ;
    float crossSectionalArea = PI * radius_m *radius_m ;
    float speed = sqrt((c.velcoityH * c.velcoityH) + (c.velcoityV * c.velcoityV));

    dragForce.x = -0.5 * airDensity * dragCoefficient * crossSectionalArea * speed * c.velcoityH ;
    dragForce.y = -0.5 * airDensity * dragCoefficient * crossSectionalArea * speed * c.velcoityV ;

    return dragForce;
}

void gravity(particle &c, bool &toggleGravity)
{
    const float g = 9.8;
    const float restitution = 0.8;
    float acceleration_y;
    float totalForce_y;

    if (IsKeyPressed(KEY_SPACE))
    {
        toggleGravity = !toggleGravity;
        c.velcoityV = 0;
        acceleration_y = 0;
        totalForce_y = 0;
    }

    if (!toggleGravity)
        return;

    
    double deltaTime = GetFrameTime();
    float dragForcee = dragForce(c).y;
    float y_m = c.centerY * 0.01 ;

    totalForce_y = (c.mass * g) + dragForcee;
    acceleration_y = totalForce_y / c.mass ;
    c.velcoityV += acceleration_y * deltaTime;
    y_m += c.velcoityV * deltaTime;
    c.centerY = y_m * 100 ;

    if (c.centerY > 600 - c.radius - 10)
    {
        c.centerY = 600 - c.radius - 10;
        c.velcoityV = -restitution * c.velcoityV;
    }
}
#endif
