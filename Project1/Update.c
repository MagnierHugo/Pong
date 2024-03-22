#include <SDL.h>

#include <stdio.h>

#include "GameState.h"
#include "main.h"
#include "Constants.h"
#include "HandleSDL.h"
#include "Ball.h"
#include "Paddle.h"
#include "Particle.h"
#include "scoreUI.h"
#include "SDLStruct.h"
#include "obstacle.h"


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
	struct Ball* ball, struct Scene scene,
	float deltaTime, bool screenWrapping
)
{
	ball->X += (ball->DirX * deltaTime * ball->Speed);
	ball->Y += (ball->DirY * deltaTime * ball->Speed);

	CollisionBallObstacles(&scene, ball);
	CollisionWithPaddles(ball, scene.Paddles, scene.SDL);

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
	if (scene.Balls[0].Speed == BALL_SPEED_TO_SPAWN_ANOTHER &&
		abs(scene.Balls[0].X - SCREEN_WIDTH / 2) < DISTANCE_TO_CENTER_LENIENCY &&
		!scene.Balls[1].Active)
	{

		scene.Balls[0].X = SCREEN_WIDTH / 2 - scene.Balls[0].Size / 2;
		scene.Balls[1].X = scene.Balls[0].X;
		scene.Balls[1].Active = true;
		scene.Balls[1].DirX = -scene.Balls[0].DirX;
		scene.Balls[1].Speed = scene.Balls[0].Speed;
		ParticlesBurst(scene.Particles, 0);
	}

	int someoneWon = 0;
	for (int i = 0; i < MAX_BALL_AMOUNT; i++)
	{
		if (!scene.Balls[i].Active) { continue; }
		someoneWon = UpdateBall(
			&scene.Balls[i], scene, deltaTime, 
			scene.ScreenWrappingActive
		);
		if (someoneWon != 0) { return someoneWon; }
	}
	return 0;
}

void Update(struct GameState state)
{
	state.currentTime = SDL_GetTicks();
    do {
		if (state.score[0] + state.score[1] > 0) SpawnObstacles(&state.scene); // no shenanigans for first round as it should be a warmup

        state.deltaTime = (SDL_GetTicks() - state.currentTime) / 1000;
        state.currentTime = SDL_GetTicks();

        state.gameSettings = HandleInput(
            state.scene.Paddles, 
            state.deltaTime, 
            state.gameSettings.ScreenWrappingActive
        );
        state.scene.ScreenWrappingActive = 
			state.gameSettings.ScreenWrappingActive;
        state.someoneWon = UpdateBalls(state.scene, state.deltaTime);
		UpdateParticles(state.scene.Particles, state.deltaTime);
        DrawScene(state);

        if (state.someoneWon != 0) {
            state.score[state.someoneWon > 0 ? 1 : 0]++;
			PreGame(state, 1);
			ResetScene(&state.scene, state.someoneWon);
            state.currentTime = SDL_GetTicks(); // make sure not to murder deltaTime
        }
    } while (state.gameSettings.ContinueRunning && 
        state.score[0] < MAX_SCORE && state.score[1] < MAX_SCORE);
}

void UpdateParticles(struct Particle* particles, float deltaTime)
{
	for (int i = 0; i < MAX_PARTICLE_AMOUNT; i++)
	{
		struct Particle* currentParticle = &particles[i];
		if (!currentParticle->Active) { continue; }
		currentParticle->X += currentParticle->DirX * deltaTime;
		currentParticle->Y += currentParticle->DirY * deltaTime;

		currentParticle->DirX *= PARTICLE_SLOWDOWN_RATE;
		currentParticle->DirY *= PARTICLE_SLOWDOWN_RATE;
		currentParticle->Size -= PARTICLE_DECAY_RATE * deltaTime;
		currentParticle->Active = currentParticle->Size > 0;
	}
}