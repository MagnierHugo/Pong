#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <SDL_mixer.h>
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
#include "Init.h"
#include "GameState.h"
#include "Update.h"
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

void BeginningCountdown(struct Scene scene, int fromWhat, SDL_Texture* background)
{
    //for (int i = fromWhat; i > 0; i--)
    //{
        WindowClear(scene.SDL.renderer, background);
        DrawBalls(scene.SDL.renderer, scene.Balls);
        DrawPaddles(scene.SDL.renderer, scene.Paddles);
        // render some texture with I as s second counter
        SDL_RenderPresent(scene.SDL.renderer); // update display
        SDL_Delay(fromWhat * 1000);
    //}
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
             CreateTexture(currentScene->SDL, "Image\\ball.png"),
            i == 0 // active | only the first ball shoud be active
        
        };
    }
}

void DrawScene(struct Scene currentScene, SDL_Texture* background)
{
    WindowClear(currentScene.SDL.renderer, background);
    DrawBalls(currentScene.SDL.renderer, currentScene.Balls);
    DrawPaddles(currentScene.SDL.renderer, currentScene.Paddles);
    SDL_RenderPresent(currentScene.SDL.renderer); // update display
    SDL_Delay(FRAMERATE);
}

int main(int argc, char* argv[])
{
    struct GameState state = {
        InitScene(), // scene
        (struct InputSummary){ true, false }, // gameSettings
        CreateTexture(state.scene.SDL, "Image\\885542.png"), // background
        0, SDL_GetTicks(), // deltaTime and currentTime
        0, { 0, 0 } // someoneWon and score
    };

    if (dance(song) != 0) {
        ErrorHandling("Error while trying to read the music", state.scene.SDL);
    }

    BeginningCountdown(state.scene, 3, state.background);

    Update(state);

    CloseSDL(state);

    return 0;
}


// sensitivity
// change ball angle?
// bonuses
// particles
// render score

