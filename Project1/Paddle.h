#include <SDL.h>

#include "Constants.h"
#include "Color.h"


struct Paddle
{
    int X;
    int Y;
    int Width;
    int Height;
    float Speed;
    //struct Color Color;
    SDL_Texture* texture;
};

void UpdatePaddle(struct Paddle* paddle, float deltaTime, int inputY);
void DrawPaddles(SDL_Renderer* renderer, struct Paddle paddles[2]);
SDL_Rect PaddleAsRect(struct Paddle paddle);