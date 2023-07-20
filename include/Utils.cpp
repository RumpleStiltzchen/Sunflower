#pragma once
#include "raylib.h"
#include "iostream"
#include "math.h"


double map(double input, double low, double high, double outlow, double outhigh)
{

    if(input > high)
        input = high;
    double percentage = input/(high - low);
    double output = ((outhigh - outlow) * percentage) + outlow;
    return output;


}


Vector2 VectorFromAngle(float angle)
{
    Vector2 output;

    output.x = 1*cos(angle);
    output.y = 1*sin(angle);

    return output;
}


