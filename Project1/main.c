#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Scene.h"
#include "Ball.h"
#include "Paddle.h"
#include "Constants.h"
#include "HandleSDL.h"
#include "Utility.h"
#include "InputSummary.h"
#include "textures.h"
#include "Music.h"


struct InputSummary HandleInput(struct Paddle paddles[2], float deltaTime, bool screenWrapping)
{
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {  
        switch (event.type)
        {
            case SDL_QUIT:
                return (struct InputSummary) { false, false };

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return (struct InputSummary) { false, false };
                }
                else if (event.key.keysym.sym == SDLK_SPACE)
                {
                    screenWrapping = !screenWrapping;
                    break;
                }

            default:
                break;    
        }

    }

    UpdatePaddle(&paddles[0], deltaTime, keyState[SDL_SCANCODE_S] - keyState[SDL_SCANCODE_W]);
    UpdatePaddle(&paddles[1], deltaTime, keyState[SDL_SCANCODE_DOWN] - keyState[SDL_SCANCODE_UP]);
    return (struct InputSummary) { true, screenWrapping };
}

struct Paddle* InitPaddles(struct SDL sdlStruct)
{
    struct Paddle* paddles = malloc(2 * sizeof(struct Paddle));
    if (paddles == NULL) {
        ErrorHandling("The memory allocation for the paddles failed", true, sdlStruct.window, sdlStruct.renderer);
    }
    paddles[0] = (struct Paddle){
        PADDLE_OFFSET_FROM_WALL,
        SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,
        PADDLE_WIDTH,
        PADDLE_HEIGHT,
        PADDLE_SPEED,
        CreateTexture(sdlStruct.window, sdlStruct.renderer, "Image\\Pad1.png")
    };

    paddles[1] = (struct Paddle){
        SCREEN_WIDTH - PADDLE_OFFSET_FROM_WALL - PADDLE_WIDTH,
        SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,
        PADDLE_WIDTH,
        PADDLE_HEIGHT,
        PADDLE_SPEED,
        CreateTexture(sdlStruct.window, sdlStruct.renderer, "Image\\Pad2.png")
    };

    return paddles;
}

struct Ball* InitBalls(struct SDL sdlStruct)
{
    struct Ball* balls = malloc(MAX_BALL_AMOUNT * sizeof(struct Ball));
    if (balls == NULL) {

        ErrorHandling("The memory allocation for the balls failed", true, sdlStruct.window, sdlStruct.renderer);
    }

    srand(time(NULL));
    for (int i = 0; i < MAX_BALL_AMOUNT; i++)
    {
        balls[i] = (struct Ball){
                SCREEN_WIDTH / 2 - BALL_SIZE / 2, // x pos
                SCREEN_HEIGHT / 2 - BALL_SIZE / 2, // y pos
                BALL_SIZE, // size
                RdmInt(-1, 1, true), // dir x
                RdmInt(-1, 1, true), // dir y
                BALL_INITIAL_SPEED, // speed
                CreateTexture(sdlStruct.window, sdlStruct.renderer, "Image\\ball.png"),
                i == 0 // only the first ball shoud be active
        };
    }

    return balls;
}

void BeginningCountdown(struct Scene scene, int fromWhat, SDL_Texture* windowTexture)
{
    for (int i = fromWhat; i > 0; i--)
    {
        WindowClear(scene.SDL.renderer, windowTexture);
        DrawBalls(scene.SDL.renderer, scene.Balls);
        DrawPaddles(scene.SDL.renderer, scene.Paddles);
        // render some texture with I as s second counter
        SDL_RenderPresent(scene.SDL.renderer); // update display
        SDL_Delay(1000);
    }
}

struct Scene InitScene()
{
    struct SDL sdl = StartSDL();
    if (sdl.exitCode == -1) { return (struct Scene ){ NULL, NULL, NULL}; }

    struct Paddle* paddles = InitPaddles(sdl);
    if (paddles == NULL) { return (struct Scene) { NULL, NULL, NULL }; }

    struct Ball* balls = InitBalls(sdl);
    if (balls == NULL) { return (struct Scene) { NULL, NULL, NULL }; }

    return (struct Scene) { balls, paddles, sdl };
}

void ResetScene(struct Scene* currentScene, int whoWon)
{
    for (int i = 0; i < 2; i++)
    {
        currentScene->Paddles[i].Y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
        currentScene->Paddles[i].Speed = PADDLE_SPEED;
    }

    for (int i = 0; i < MAX_BALL_AMOUNT; i++)
    {
        currentScene->Balls[i] = (struct Ball){
            SCREEN_WIDTH / 2 - BALL_SIZE / 2, // x pos
            SCREEN_HEIGHT / 2 - BALL_SIZE / 2, // y pos
            BALL_SIZE, // size
            whoWon, // dir x
            RdmInt(-1, 1, true), // dir y
            BALL_INITIAL_SPEED, // speed
             CreateTexture(currentScene->SDL.window, currentScene->SDL.renderer, "Image\\ball.png"),
            i == 0 // active | only the first ball shoud be active
        
        };
    }
}

void DrawScene(struct Scene currentScene, SDL_Texture* windowTexture)
{
    WindowClear(currentScene.SDL.renderer, windowTexture);
    DrawBalls(currentScene.SDL.renderer, currentScene.Balls);
    DrawPaddles(currentScene.SDL.renderer, currentScene.Paddles);
    SDL_RenderPresent(currentScene.SDL.renderer); // update display
    SDL_Delay(FRAMERATE);
}

int main(int argc, char* argv[])
{
    struct Scene scene = InitScene();
    SDL_Texture* windowTexture = CreateTexture(scene.SDL.window, scene.SDL.renderer, "Image\\885542.png");
    int score[2] = { 0, 0 };
    
    float deltaTime;
    int someoneWon; // -1 -> left won | 1 right won | 0 no one won
    struct InputSummary gameSettings = { true, false }; // didn t find a more fitting name for it
    BeginningCountdown(scene, 3, windowTexture);
    float currentTime = SDL_GetTicks();
    do
    {
        WindowClear(scene.SDL.renderer, windowTexture);

        deltaTime = (SDL_GetTicks() - currentTime) / 1000;
        currentTime = SDL_GetTicks();

        gameSettings = HandleInput(scene.Paddles, deltaTime, gameSettings.ScreenWrappingActive);
        scene.ScreenWrappingActive = gameSettings.ScreenWrappingActive;
        someoneWon = UpdateBalls(scene, deltaTime);

        DrawScene(scene, windowTexture);

        if (someoneWon != 0)
        {
            score[someoneWon > 0 ? 1 : 0]++;
            printf("%d : %d", score[0], score[1]);
            BeginningCountdown(scene, 1, windowTexture);
            ResetScene(&scene, someoneWon);
            currentTime = SDL_GetTicks(); // make sure not to murder deltaTime
        }

    } while (gameSettings.ContinueRunning && score[0] < MAX_SCORE && score[1] < MAX_SCORE);

    CloseSDL(scene);

    return 0;
}


// sensitivity
// change ball angle?
// bonuses
// particles
// render score

