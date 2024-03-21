#include <SDL.h>
#include <stdbool.h>

#include "Scene.h"
#include "Constants.h"
#include "Paddle.h"
#include "Color.h"
#include "Vector2.h"




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

static void HandleCollisionWithPaddle(struct Ball* ball, struct Paddle* relevantPaddle, SDL_Window* window)
{
	ball->DirX *= -1;
	ball->Speed += BALL_SPEED_INCREMENT;
	// get the paddle -> ball vector and set it as new ball velocity
	struct Vector2 paddleBallVec = { relevantPaddle->X + relevantPaddle->Width / 2 - ball->X , relevantPaddle->Y - ball->Y };
	Normalize(paddleBallVec);
	SDL_SetWindowTitle(window, SDL_GetWindowTitle(window)[1] == 'o' ? "Ping" : "Pong"); // knowing it s the only character iffering it s faster tço check for it directly
	/*ball->DirX = paddleBallVec.X;
	ball->DirY = paddleBallVec.Y;*/
}

static int UpdateBall(struct Ball* ball, struct Paddle paddles[2], float deltaTime, SDL_Window* window, bool screenWrapping) {
	ball->X += (ball->DirX * deltaTime * ball->Speed);
	ball->Y += (ball->DirY * deltaTime * ball->Speed);
	if (ball->X < SCREEN_HEIGHT / 4) { // check wether the paddle is in a region somewhat relevant to the paddle before doing a billion checks
		if (ball->X <= paddles[0].X + paddles[0].Width &&
			paddles[0].Y <= ball->Y + ball->Size &&
			paddles[0].Y + paddles[0].Height >= ball->Y
			) { // collision with left paddle
				ball->X = paddles[0].X + paddles[0].Width + 1; // get it out of the paddle in order to avoid it glitching
				HandleCollisionWithPaddle(ball, &paddles[0], window);
		}
	} else if (ball->X + ball->Size > 3 * SCREEN_HEIGHT / 4) {
		if (ball->X + ball->Size >= paddles[1].X &&
			paddles[1].Y <= ball->Y + ball->Size &&
			paddles[1].Y + paddles[1].Height >= ball->Y) { // collision with right paddle
				ball->X = paddles[1].X - ball->Size - 1;
				HandleCollisionWithPaddle(ball, &paddles[1], window);
		}
	}
	if (ball->Y + ball->Size >= SCREEN_HEIGHT) {
		if (screenWrapping)
		{
			ball->Y = 1;
		}
		else
		{
			ball->Y = SCREEN_HEIGHT - ball->Size - 1;
			ball->DirY *= -1;
		}
	} else if (ball->Y <= 0)
	{
		if (screenWrapping)
		{
			ball->Y = SCREEN_HEIGHT - ball->Size - 1;
		}
		else
		{
			ball->DirY *= -1;
			ball->Y = 1;
		}
		
	} // get it out of the border in order to avoid it glitching and change trajectory
	
	if (ball->X + ball->Size >= SCREEN_WIDTH) { return -1; } // collide on the right border
	if (ball->X <= 0) { return 1; } // collide on the left border
	return 0;
}

// just the clean version (pre norm version) of the vile abberation just above in case you wish to keep ur eyes in a somewhat decent health

#pragma region Tiny comment

//static void UpdateBall(struct Ball* ball, struct Paddle paddles[2], float deltaTime, SDL_Window* window)
//{
//	ball->X += (ball->DirX * deltaTime * ball->Speed);
//	ball->Y += (ball->DirY * deltaTime * ball->Speed);
//
//	if (ball->X < SCREEN_HEIGHT / 4) // check wether the paddle is in a region somewhat relevant to the paddle before doing a billion checks
//	{ 
//		if (
//			ball->X <= paddles[0].X + paddles[0].Width &&
//			paddles[0].Y <= ball->Y + ball->Size &&
//			paddles[0].Y + paddles[0].Height >= ball->Y
//			) // collision with left paddle
//		{ 
//			ball->X = paddles[0].X + paddles[0].Width + 1; // get it out of the paddle in order to avoid it glitching
//			HandleCollisionWithPaddle(ball, &paddles[0], window);
//		}
//	}
//	else if (ball->X + ball->Size > 3 * SCREEN_HEIGHT / 4)
//	{
//		if (
//			ball->X + ball->Size >= paddles[1].X &&
//			paddles[1].Y <= ball->Y + ball->Size &&
//			paddles[1].Y + paddles[1].Height >= ball->Y
//			) // collision with right paddle
//		{
//			ball->X = paddles[1].X - ball->Size - 1;
//			HandleCollisionWithPaddle(ball, &paddles[1], window);
//		}
//	}
//	if (ball->Y + ball->Size >= SCREEN_HEIGHT) // collide on the bottom border
//	{ 
//		ball->Y = SCREEN_HEIGHT - ball->Size - 1; // get it out of the border in order to avoid it glitching
//		ball->DirY *= -1;
//	}
//	else if (ball->Y <= 0) // collide on the top border
//	{ 
//		ball->DirY *= -1; // get it out of the border in order to avoid it glitching
//		ball->Y = 1;
//	}
//	if (ball->X + ball->Size >= SCREEN_WIDTH) // collide on the right border
//	{ 
//		return -1;
//	}
//	if (ball->X <= 0) // collide on the left border
//	{
//		return 1;
//	}
// return 0;
//
//}

#pragma endregion

SDL_Rect BallAsRect(struct Ball ball)
{
	return (SDL_Rect) { ball.X, ball.Y, ball.Size, ball.Size };
}

int UpdateBalls(struct Scene scene, float deltaTime)
{
	int someoneWon;
	for (int i = 0; i < MAX_BALL_AMOUNT; i++)
	{
		if (!scene.Balls[i].Active) { continue; }
		someoneWon = UpdateBall(&scene.Balls[i], scene.Paddles, deltaTime, scene.SDL.window, scene.ScreenWrappingActive);
		if (someoneWon != 0) { return someoneWon; }
	}
	return 0;
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