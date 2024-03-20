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
    //struct Color Color;
    SDL_Texture* texture;
    bool Active;
};

SDL_Rect BallAsRect(struct Ball ball);
void UpdateBalls(struct Ball* balls, struct Paddle paddles[2], float deltaTime);
void DrawBalls(SDL_Renderer* renderer, struct Ball* balls);
