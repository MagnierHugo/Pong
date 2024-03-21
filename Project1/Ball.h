#include <SDL.h>

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
int UpdateBalls(struct Scene scene, float deltaTime);
void DrawBalls(SDL_Renderer* renderer, struct Ball* balls);
