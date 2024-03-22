#include <SDL.h>
#include <stdbool.h>

#include "Scene.h"
#include "Constants.h"
#include "Paddle.h"
#include "Color.h"
#include "Vector2.h"
#include "Music.h"
#include "HandleSDL.h"


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


SDL_Rect BallAsRect(struct Ball ball)
{
	return (SDL_Rect) { ball.X, ball.Y, ball.Size, ball.Size };
}

void DrawBalls(SDL_Renderer* renderer, struct Ball* balls)
{
	for (int i = 0; i < MAX_BALL_AMOUNT; i++)
	{
		if (!balls[i].Active) { continue; }

		struct Ball curBall = balls[i];
		SDL_Rect ballRect = BallAsRect(curBall);

		//SDL_SetRenderDrawColor(renderer, curBall.Color.R, curBall.Color.G, curBall.Color.B, curBall.Color.A);
		//SDL_RenderFillRect(renderer, &ballRect);
		SDL_RenderCopy(renderer, curBall.texture, NULL, &ballRect);
	}
}

static void HandleCollisionWithPaddle(
	struct Ball* ball, struct Paddle* relevantPaddle, 
	struct SDL sdlStruct
)
{
	ball->DirX *= -1;
	ball->Speed += BALL_SPEED_INCREMENT;
	// get the paddle -> ball vector and set it as new ball velocity
	struct Vector2 paddleBallVec = { relevantPaddle->X + relevantPaddle->Width / 2 - ball->X , relevantPaddle->Y - ball->Y };
	Normalize(paddleBallVec);

	PlaySound(bounce, sdlStruct);

	SDL_SetWindowTitle(sdlStruct.window, SDL_GetWindowTitle(sdlStruct.window)[1] == 'o' ? "Ping" : "Pong"); // knowing it s the only character iffering it s faster to check for it directly
}

void CollisionWithPaddles(
	struct Ball* ball, struct Paddle paddles[2], 
	struct SDL sdlStruct
)
{
	if (
		ball->X <= paddles[0].X + paddles[0].Width &&
		paddles[0].Y <= ball->Y + ball->Size &&
		paddles[0].Y + paddles[0].Height >= ball->Y
		) // collision with left paddle
	{
		ball->X = paddles[0].X + paddles[0].Width + 1; // get it out of the paddle in order to avoid it glitching
		HandleCollisionWithPaddle(ball, &paddles[0], sdlStruct);
	}
	if (
		ball->X + ball->Size >= paddles[1].X &&
		paddles[1].Y <= ball->Y + ball->Size &&
		paddles[1].Y + paddles[1].Height >= ball->Y
		) // collision with right paddle
	{
		ball->X = paddles[1].X - ball->Size - 1;
		HandleCollisionWithPaddle(ball, &paddles[1], sdlStruct);
	}
}

int CheckGoal(struct Ball* ball, struct SDL sdlStruct)
{
	if (ball->X + ball->Size >= SCREEN_WIDTH) { // collide on the right border
		PlaySound(goal, sdlStruct);
		return -1;
	}
	if (ball->X <= 0) { // collide on the left border
		PlaySound(goal, sdlStruct);
		return 1;
	}
	return 0;
}