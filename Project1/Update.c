#include <SDL.h>

#include <stdio.h>

#include "GameState.h"
#include "main.h"
#include "Constants.h"
#include "HandleSDL.h"
#include "Ball.h"
#include "Paddle.h"


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

	paddle->Y += (inputY * deltaTime * paddle->Speed);
}

static int UpdateBall(
	struct Ball* ball, struct Paddle paddles[2],
	float deltaTime, struct Scene scene, bool screenWrapping
)
{
	ball->X += (ball->DirX * deltaTime * ball->Speed);
	ball->Y += (ball->DirY * deltaTime * ball->Speed);

	CollisionWithPaddles(ball, paddles, scene.SDL);

	if (ball->Y + ball->Size >= SCREEN_HEIGHT) {

		if (screenWrapping) {
			ball->Y = 1;
		}
		else {
			ball->Y = SCREEN_HEIGHT - ball->Size - 1;
			ball->DirY *= -1;
		}

	}
	else if (ball->Y <= 0) {

		if (screenWrapping) {
			ball->Y = SCREEN_HEIGHT - ball->Size - 1;
		}
		else {
			ball->DirY *= -1;
			ball->Y = 1;
		}

	} // get it out of the border in order to avoid it glitching and change trajectory

	return CheckGoal(ball, scene);
}

static int UpdateBalls(struct Scene scene, float deltaTime)
{
	int someoneWon;
	for (int i = 0; i < MAX_BALL_AMOUNT; i++)
	{
		if (!scene.Balls[i].Active) { continue; }

		someoneWon = UpdateBall(
			&scene.Balls[i], scene.Paddles, deltaTime, 
			scene, scene.ScreenWrappingActive
		);

		if (someoneWon != 0) { return someoneWon; }
	}
	return 0;
}

void Update(struct GameState state)
{
	state.currentTime = SDL_GetTicks();
    do {
        state.deltaTime = (SDL_GetTicks() - state.currentTime) / 1000;
        state.currentTime = SDL_GetTicks();

        state.gameSettings = HandleInput(
            state.scene.Paddles, 
            state.deltaTime, 
            state.gameSettings.ScreenWrappingActive
        );

        state.scene.ScreenWrappingActive = state.gameSettings.ScreenWrappingActive;
        state.someoneWon = UpdateBalls(state.scene, state.deltaTime);

        DrawScene(state.scene, state.background);

        if (state.someoneWon != 0) {
            state.score[state.someoneWon > 0 ? 1 : 0]++;
            printf("%d : %d\n", state.score[0], state.score[1]);
			PreGame(state.scene, 1, state.background);
            ResetScene(&state.scene, state.someoneWon);
            state.currentTime = SDL_GetTicks(); // make sure not to murder deltaTime
        }

    } while (
        state.gameSettings.ContinueRunning && 
        state.score[0] < MAX_SCORE && 
        state.score[1] < MAX_SCORE );
}