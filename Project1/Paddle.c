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

void UpdatePaddle(struct Paddle* paddle, float deltaTime, int inputY)
{
	if (inputY > 0 && paddle->Y + paddle->Height >= SCREEN_HEIGHT)
	{
		paddle->Y = SCREEN_HEIGHT - paddle->Height;
		return;
	}

	if (inputY < 0 && paddle->Y <= 0)
	{
		paddle->Y = 0;
		return;
	}

	paddle->Y += (int)(inputY * deltaTime * paddle->Speed);
}

SDL_Rect PaddleAsRect(struct Paddle paddle)
{
	return (SDL_Rect) { paddle.X, paddle.Y, paddle.Width, paddle.Height };
}

void DrawPaddles(SDL_Renderer* renderer, struct Paddle paddles[2])
{
	for (int i = 0; i < 2; i++)
	{
		struct Paddle curPaddle = paddles[i];
		SDL_Rect paddleRect = PaddleAsRect(curPaddle);

		//SDL_SetRenderDrawColor(renderer, curPaddle.Color.R, curPaddle.Color.G, curPaddle.Color.B, curPaddle.Color.A);
		//SDL_RenderFillRect(renderer, &paddleRect);
		SDL_RenderCopy(renderer, curPaddle.texture, NULL, &paddleRect);
	}
}