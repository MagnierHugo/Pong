#include <SDL.h>
#include <stdbool.h>

#include "Constants.h"

#ifndef COLOR

#define COLOR
#include "Color.h"

#endif

#include "Paddle.h"
#include "Vector2.h"


struct Ball
{
	int X;
	int Y;
	int Size;

	int DirX;
	int DirY;
	int Speed;

	struct Color Color;

	bool Active;
};

static void HandleCollisionWithPaddle(struct Ball* ball, struct Paddle* relevantPaddle, SDL_Window* window)
{
	ball->DirX *= -1;
	// get the paddle -> ball vector and set it as new ball velocity
	struct Vector2 paddleBallVec = { relevantPaddle->X + relevantPaddle->Width / 2 - ball->X , relevantPaddle->Y - ball->Y };
	Normalize(&paddleBallVec);
	SDL_SetWindowTitle(window, SDL_GetWindowTitle(window)[1] == 'O' ? "PING" : "PONG"); // knowing it s the only character iffering it s faster tço check for it directly
	/*ball->DirX = paddleBallVec.X;
	ball->DirY = paddleBallVec.Y;*/
}

static void UpdateBall(struct Ball* ball, struct Paddle paddles[2], float deltaTime, SDL_Window* window)
{
	ball->X += (ball->DirX * deltaTime * ball->Speed);
	ball->Y += (ball->DirY * deltaTime * ball->Speed);

	if (ball->X < SCREEN_HEIGHT / 4) // check wether the paddle is in a region somewhat relevant to the paddle before doing a billion checks
	{
		if (
			ball->X <= paddles[0].X + paddles[0].Width &&
			paddles[0].Y <= ball->Y + ball->Size &&
			paddles[0].Y + paddles[0].Height >= ball->Y
			) // collision with left paddle
		{
			ball->X = paddles[0].X + paddles[0].Width + 1; // get it out of the paddle in order to avoid it glitching
			HandleCollisionWithPaddle(ball, &paddles[0], window);
		}
	}
	else if (ball->X + ball->Size > 3 * SCREEN_HEIGHT / 4)
	{

		if (ball->X + ball->Size >= paddles[1].X && paddles[1].Y <= ball->Y + ball->Size && paddles[1].Y + paddles[1].Height >= ball->Y) // collision with right paddle
		{
			ball->X = paddles[1].X - ball->Size - 1;
			HandleCollisionWithPaddle(ball, &paddles[1], window);
		}
	}

	if (ball->Y + ball->Size >= SCREEN_HEIGHT) // collide on the bottom border
	{
		ball->Y = SCREEN_HEIGHT - ball->Size - 1; // get it out of the border in order to avoid it glitching
		ball->DirY *= -1;
	}
	else if (ball->Y <= 0) // collide on the top border
	{
		ball->DirY *= -1; // get it out of the border in order to avoid it glitching
		ball->Y = 1;
	}

	if (ball->X + ball->Size >= SCREEN_WIDTH) // collide on the right border
	{
		ball->DirX *= -1;
	}
	else if (ball->X <= 0) // collide on the left border
	{
		ball->DirX *= -1;
	}

}

SDL_Rect BallAsRect(struct Ball ball)
{
	return (SDL_Rect) { ball.X, ball.Y, ball.Size, ball.Size };
}

void UpdateBalls(struct Ball* balls, struct Paddle paddles[2], float deltaTime, SDL_Window* window)
{
	for (int i = 0; i < MAX_BALL_AMOUNT; i++)
	{
		if (!balls[i].Active) { continue; }
		UpdateBall(&balls[i], paddles, deltaTime, window);
	}
}

void DrawBalls(SDL_Renderer* renderer, struct Ball* balls)
{
	for (int i = 0; i < MAX_BALL_AMOUNT; i++)
	{
		if (!balls[i].Active) { continue; }

		struct Ball curBall = balls[i];
		SDL_Rect ballRect = BallAsRect(curBall);

		SDL_SetRenderDrawColor(renderer, curBall.Color.R, curBall.Color.G, curBall.Color.B, curBall.Color.A);
		SDL_RenderFillRect(renderer, &ballRect);
	}
}