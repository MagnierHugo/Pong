#pragma once

#include <math.h>


struct Vector2 { float X, Y; };

float Magnitude(struct Vector2 vec)
{
    return sqrt(vec.X * vec.Y + vec.X * vec.Y);
}

// Function to normalize a vector
struct Vector2 Normalize(struct Vector2 vec)
{
    float magnitude = Magnitude(vec);
    if (magnitude != 0)
    {
        vec.X /= magnitude;
        vec.Y /= magnitude;
    }
    return vec;
}