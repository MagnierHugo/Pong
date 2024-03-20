#include <SDL.h>

#include "Constants.h"

#ifndef COLOR

#define COLOR
#include "Color.h"

#endif

struct Ball
{
    int X;
    int Y;
    int Size;
    int DirX;
    int DirY;
    int Speed;
    struct Color Color;
    float LastTimeTouchedPaddle;
};

SDL_Rect BallAsRect(struct Ball ball);
void UpdateBalls(struct Ball* balls, int ballAmount, struct Paddle paddles[2], float deltaTime);
void DrawBalls(SDL_Renderer* renderer, struct Ball* balls, int ballAmount);
