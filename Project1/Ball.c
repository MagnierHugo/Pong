#include <SDL.h>
#include <stdbool.h>

#include "Scene.h"
#include "Constants.h"
#include "Paddle.h"
#include "Particle.h"
#include "Color.h"
#include "Vector2.h"
#include "Music.h"
#include "HandleSDL.h"


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
	if (ball->Speed > BALL_SPEED_THRESHOLD_TO_SHORTEN)
	{
		relevantPaddle->Height -= PADDLE_SHORTENING_AMOUNT;
	}

	PlaySound(bounce, sdlStruct);

	SDL_SetWindowTitle(
		sdlStruct.window, 
		SDL_GetWindowTitle(sdlStruct.window)[1] == 'o' ? "Ping" : "Pong"
	); // knowing it s the only character iffering it s faster to check for it directly
}

void CollisionWithPaddles(
	struct Ball* ball, struct Paddle paddles[2], 
	struct SDL sdlStruct
)
{
	if (
		ball->X <= paddles[0].X + paddles[0].Width &&
		!(ball->X < paddles[0].X) &&
		paddles[0].Y <= ball->Y + ball->Size &&
		paddles[0].Y + paddles[0].Height >= ball->Y
		) // collision with left paddle
	{
		ball->X = paddles[0].X + paddles[0].Width + 1; // get it out of the paddle in order to avoid it glitching
		HandleCollisionWithPaddle(ball, &paddles[0], sdlStruct);
	}
	if (
		ball->X + ball->Size >= paddles[1].X &&
		!(ball->X + ball->Size > paddles[1].X + paddles[1].Width) &&
		paddles[1].Y <= ball->Y + ball->Size &&
		paddles[1].Y + paddles[1].Height >= ball->Y
		) // collision with right paddle
	{
		ball->X = paddles[1].X - ball->Size - 1;
		HandleCollisionWithPaddle(ball, &paddles[1], sdlStruct);
	}
}

int CheckGoal(struct Ball* ball, struct Scene scene)
{
	if (ball->X + ball->Size >= SCREEN_WIDTH + OUT_OF_BOUNDS_THRESHOLD) { // left the screen to the right
		PlaySound(goal, scene.SDL);
		ParticlesBurst(scene.Particles, -1);
		return -1;
	}
	if (ball->X <= -OUT_OF_BOUNDS_THRESHOLD) { //  left the screen to the left
		PlaySound(goal, scene.SDL);
		ParticlesBurst(scene.Particles, 1);
		return 1;
	}
	return 0;
}