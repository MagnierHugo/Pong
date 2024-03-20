#include <SDL.h>
#include "Constants.h"
#ifndef COLOR

#define COLOR
#include "Color.h"

#endif

struct Paddle
{
    int X;
    int Y;
    int Width;
    int Height;
    int Speed;
    //struct Color Color;
    SDL_Texture* texture;
};

void UpdatePaddle(struct Paddle* paddle, float deltaTime, int inputY);

SDL_Rect PaddleAsRect(struct Paddle paddle);