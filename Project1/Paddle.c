#include <SDL.h>
#include <stdio.h>

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


SDL_Rect PaddleAsRect(struct Paddle paddle)
{
	return (SDL_Rect) { (int) paddle.X, (int) paddle.Y, paddle.Width, paddle.Height };
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