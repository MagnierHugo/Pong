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




#pragma region Legacy SDL Handling

int InitSDL()
{
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }

    return 1;
}

SDL_Window* InitWindow()
{
    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow(
        "PONG",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // screen pos (x, y)
        SCREEN_WIDTH, SCREEN_HEIGHT, // screen width (w, h)
        SDL_WINDOW_SHOWN | SDL_RENDERER_PRESENTVSYNC
    );

    return window;
}

SDL_Renderer* InitRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    return renderer;
}

#pragma endregion

void WindowClear(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // more of a fill
}

bool HandleInput(struct Paddle paddles[2])
{
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (!CheckExit(event))
        {
            return false;
        }

        UpdatePaddle(&paddles[0], 1, keyState[SDL_SCANCODE_S] - keyState[SDL_SCANCODE_Z]);
        UpdatePaddle(&paddles[1], 1, keyState[SDL_SCANCODE_DOWN] - keyState[SDL_SCANCODE_UP]);
    }
    return true;
}

struct Paddle* InitPaddles()
{
    int paddleWidth = 10;
    int paddleHeight = 80;
    int paddleSpeed = 15;
    int paddleOffsetFromWall = 30;

    struct Paddle* paddles = malloc(2 * sizeof(struct Paddle));
    if (paddles == NULL) {
        printf("The memory allocation for the paddles failed");
        return NULL;
    }
    paddles[0] = (struct Paddle){
        paddleOffsetFromWall,
        SCREEN_HEIGHT / 2 - paddleHeight / 2, // half the height of the screen - half the paddle size
        paddleWidth,
        paddleHeight,
        paddleSpeed,
        (struct Color) {0, 0, 0, 255}
    };

    paddles[1] = (struct Paddle){
        SCREEN_WIDTH - paddleOffsetFromWall - paddleWidth,
        SCREEN_HEIGHT / 2 - paddleHeight / 2, // half the height of the screen - half the paddle size
        paddleWidth,
        paddleHeight,
        paddleSpeed,
        (struct Color) {0, 0, 0, 255}
    };

    return paddles;
}

struct Ball InitBall()
{

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
 
    #pragma region Legacy SDL

    /*if (InitSDL() < 0) { return -1; }
    SDL_Window* window = InitWindow();
    if (window == NULL)
    {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    SDL_Renderer* renderer = InitRenderer(window);
    if (renderer == NULL)
    {
        printf("Erreur creation rendu SDL\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
    }*/

#pragma endregion

    struct SDL sdl = StartSDL();
    if (sdl.exitCode == -1) { return -1; }
    struct Paddle* paddles = InitPaddles();

    if (paddles == NULL)
    {
        return -1;
    }
    srand(time(NULL));

    int ballAmount;
    printf("Enter the number of balls: ");
    int _ = scanf("%d", &ballAmount);

    struct Ball* balls = (struct Ball*) malloc(ballAmount * sizeof(struct Ball));
    if (balls == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    for (int i = 0; i < ballAmount; i++)
    {
        balls[i] = (struct Ball){
            RdmInt(0, SCREEN_WIDTH - 100, false), // - max size for them not to be stuck on walls
            RdmInt(0, SCREEN_HEIGHT - 100, false),
            RdmInt(10, 100, false), // size
            RdmInt(-10, 10, true),
            RdmInt(-10, 10, true),
            RdmInt(1, 2, false),
            (struct Color) { RdmInt(0, 255, false), RdmInt(0, 255, false), RdmInt(0, 255, false), 255 }
        };
    }

    bool continueRunning = true;
    while (continueRunning)
    {
        continueRunning = HandleInput(paddles);


        UpdateBalls(balls, ballAmount, 1);
        WindowClear(sdl.renderer);
        DrawBalls(sdl.renderer, balls, ballAmount);
        DrawPaddles(sdl.renderer, paddles);
        SDL_RenderPresent(sdl.renderer); // update display
        SDL_Delay(FRAMERATE); 
    }

    // Fermeture de la fenêtre et de la SDL
    SDL_DestroyRenderer(sdl.renderer);
    SDL_DestroyWindow(sdl.window);
    SDL_Quit();

    return 0;
}

// jeu a la manette
// sensi
// ball collisions
// comments for where sound 