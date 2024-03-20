#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Ball.h"
#include "Paddle.h"
#include "Constants.h"
#include "HandleSDL.h"


void WindowClear(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // more of a fill
}

bool HandleInput(struct Paddle paddles[2], float deltaTime)
{
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (CheckExit(event))
        {
            return false;
        }
    }

    UpdatePaddle(&paddles[0], deltaTime, keyState[SDL_SCANCODE_S] - keyState[SDL_SCANCODE_W]);
    UpdatePaddle(&paddles[1], deltaTime, keyState[SDL_SCANCODE_DOWN] - keyState[SDL_SCANCODE_UP]);
    return true;
}

struct Paddle* InitPaddles()
{
    int paddleWidth = 25;
    int paddleHeight = 170;
    int paddleSpeed = 750;
    int paddleOffsetFromWall = 100;

    struct Paddle* paddles = malloc(2 * sizeof(struct Paddle));
    if (paddles == NULL) {
        printf("The memory allocation for the paddles failed");
        return NULL;
    }
    paddles[0] = (struct Paddle){
        paddleOffsetFromWall,
        SCREEN_HEIGHT / 2 - paddleHeight / 2,
        paddleWidth,
        paddleHeight,
        paddleSpeed,
        (struct Color) {0, 0, 0, 255}
    };

    paddles[1] = (struct Paddle){
        SCREEN_WIDTH - paddleOffsetFromWall - paddleWidth,
        SCREEN_HEIGHT / 2 - paddleHeight / 2,
        paddleWidth,
        paddleHeight,
        paddleSpeed,
        (struct Color) {0, 0, 0, 255}
    };

    return paddles;
}

struct Ball* InitBalls(int side)
{
    struct Ball* balls = (struct Ball*) malloc(MAX_BALL_AMOUNT * sizeof(struct Ball));
    if (balls == NULL) {
        printf("The memory allocation for the balls failed\n");
        return NULL;
    }

    srand(time(NULL));
    for (int i = 0; i < MAX_BALL_AMOUNT; i++)
    {

        balls[i] = (struct Ball){
                SCREEN_WIDTH / 2 - 25,
                SCREEN_HEIGHT / 2 - 25,
                50, // size
                side == 0 ? RdmInt(-1, 1, true) : side > 0 ? 1 : -1,
                RdmInt(-1, 1, true),
                500,
                (struct Color) { RdmInt(0, 255, false), RdmInt(0, 255, false), RdmInt(0, 255, false), 255},
                i == 0 // only the first ball shoud be active
        };
    }

    return balls;
}

int RdmInt(int min, int max, bool nonZero)
{
    int rdm;
    do
    {
        rdm = min + rand() % (max - min + 1);
    } while (nonZero && rdm == 0);

    return rdm;
}

int main(int argc, char* argv[])
{
    struct SDL sdl = StartSDL();
    if (sdl.exitCode == -1) { return -1; }

    struct Paddle* paddles = InitPaddles();
    if (paddles == NULL) { return -1; }

    struct  Ball* balls = InitBalls(0);
    if (balls == NULL) { return -1; }

    int score[2] = { 0, 0 };
    

    WindowClear(sdl.renderer);
    DrawBalls(sdl.renderer, balls);
    DrawPaddles(sdl.renderer, paddles);
    SDL_RenderPresent(sdl.renderer); // update display
    SDL_Delay(1500);

    float currentTime = SDL_GetTicks();
    float deltaTime;
    bool continueRunning = true;
    while (continueRunning)
    {
        deltaTime = (SDL_GetTicks() - currentTime) / 1000;
        currentTime = SDL_GetTicks();

        continueRunning = HandleInput(paddles, deltaTime);


        UpdateBalls(balls, paddles, deltaTime, sdl.window);
        WindowClear(sdl.renderer);
        DrawBalls(sdl.renderer, balls);
        DrawPaddles(sdl.renderer, paddles);
        SDL_RenderPresent(sdl.renderer); // update display
        SDL_Delay(FRAMERATE); 
    }

    // Fermeture de la fen�tre et de la SDL
    SDL_DestroyRenderer(sdl.renderer);
    SDL_DestroyWindow(sdl.window);
    SDL_Quit();

    return 0;
}

// jeu a la manette
// sensi
// ball collisions
// comments for where sound 