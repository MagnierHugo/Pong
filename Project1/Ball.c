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
};

static void UpdateBall(struct Ball* ball, struct Paddle paddles[2], float deltaTime)
{
	ball->X += (int)(ball->DirX * deltaTime * ball->Speed);
	ball->Y += (int)(ball->DirY * deltaTime * ball->Speed);

	if (ball->X + ball->Size >= SCREEN_WIDTH || ball->X <= 0)
	{
		ball->DirX *= -1;
	}
	if (ball->Y + ball->Size >= SCREEN_HEIGHT || ball->Y <= 0)
	{
		ball->DirY *= -1;
	}
}

SDL_Rect BallAsRect(struct Ball ball)
{
	return (SDL_Rect) { ball.X, ball.Y, ball.Size, ball.Size };
}

void UpdateBalls(struct Ball* balls, int ballAmount, struct Paddle paddles[2], float deltaTime)
{



	for (int i = 0; i < ballAmount; i++)
	{
		UpdateBall(&balls[i], paddles, deltaTime);
	}
}

void DrawBalls(SDL_Renderer* renderer, struct Ball* balls, int ballAmount)
{
	for (int i = 0; i < ballAmount; i++)
	{
		struct Ball curBall = balls[i];
		SDL_Rect ballRect = BallAsRect(curBall);

		SDL_SetRenderDrawColor(renderer, curBall.Color.R, curBall.Color.G, curBall.Color.B, curBall.Color.A);
		SDL_RenderFillRect(renderer, &ballRect);
	}
}
