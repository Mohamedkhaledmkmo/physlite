#ifndef PHYSICS_H
#define PHYSICS_H

#include <raylib.h>
#include <cmath>
#include <iostream>
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

struct particle
{
    float centerX = 0;
    float centerY = 0;
    float radius = 20;
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
               float baseThick = 20,
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
    DrawLineEx(f.point2, f.point3, f.baseThick, f.color);
    DrawLineEx(f.point3, f.point4, f.sideThick, f.color);
}

void control(particle &c, frame &f, int width, int height)

{
    int motion = 10;
    int upperLimit = c.radius;
    int lowerLimit = height - c.radius - f.baseThick / 2;
    int rightSideLimit = width - c.radius - f.sideThick / 2;
    int leftSideLimit = c.radius + f.sideThick / 2;

    if (IsKeyDown(KEY_UP))
    {
        if (c.centerY > upperLimit)
            c.centerY -= motion;
        else
            c.centerY = upperLimit;
    }

    else if (IsKeyDown(KEY_DOWN))
    {
        if (c.centerY < lowerLimit)
            c.centerY += motion;
        else
            c.centerY = lowerLimit;
    }

    else if (IsKeyDown(KEY_RIGHT))
    {
        if (c.centerX < rightSideLimit)
            c.centerX += motion;
        else
            c.centerX = rightSideLimit;
    }

    else if (IsKeyDown(KEY_LEFT))
    {
        if (c.centerX > leftSideLimit)
            c.centerX -= motion;
        else
            c.centerX = leftSideLimit;
    }
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

inline int sign(float x)
{
    if (x > 0)
        return 1;
    if (x < 0)
        return -1;
    return 0;
}

// float contactForce(particle &c)
// {
//     float penDepthPx = (c.radius + c.centerY) - (600 - 10);
//     float penDepth = penDepthPx * 0.01f;
//     if (penDepth <= 0.0f)
//         return 0.0f;

//     float particleStiff = 480;
//     float particleDamp = 2 * sqrt(particleStiff * c.mass);
//     float floorStiff = 1.6 * 1e9;
//     float floorDamp = 2 * sqrt(floorStiff);
//     float effStiff = 1.0f / (1.0f / particleStiff + 1.0f / floorStiff);
//     float effDamp = 1.0f / (1.0f / particleDamp + 1.0f / floorDamp);

//     float springTerm = -effStiff * penDepth;
//     float dampingTerm = -effDamp * c.velcoityV;
//     float contactForce = springTerm + dampingTerm;

//     return contactForce;
// }

Vector2 dragForce(particle &c)
{
    Vector2 dragForce;
    const float airDensity = 1.2;
    const float dragCoefficient = 0.47;
    float radius_m = c.radius * 0.01;
    float crossSectionalArea = PI * radius_m * radius_m;
    float speed = sqrt((c.velcoityH * c.velcoityH) + (c.velcoityV * c.velcoityV));

    dragForce.x = -0.5 * airDensity * dragCoefficient * crossSectionalArea * speed * c.velcoityH;
    dragForce.y = -0.5 * airDensity * dragCoefficient * crossSectionalArea * speed * c.velcoityV;

    return dragForce;
}

void gravity(particle &c, frame &f , int width , int height, bool &toggleGravity)
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
    float y_m = c.centerY * 0.01;
    

    totalForce_y = (c.mass * g) + dragForcee ;
    acceleration_y = totalForce_y / c.mass;
    c.velcoityV += acceleration_y * deltaTime;
    y_m += c.velcoityV * deltaTime;
    c.centerY = y_m * 100;
    float limit = height - f.baseThick/2 - c.radius;
    if (c.centerY > limit)
    {
        c.centerY = limit;
        c.velcoityV = -0.8 * c.velcoityV;
    }
}
#endif
