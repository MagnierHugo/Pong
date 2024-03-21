#include <SDL.h>
#include <stdbool.h>

#include "Constants.h"
#include "Color.h"

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
void CollisionWithPaddles(struct Ball* ball, struct Paddle paddles[2], SDL_Window* window);
void DrawBalls(SDL_Renderer* renderer, struct Ball* balls);
