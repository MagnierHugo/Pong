#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Scene.h"
#include "ScoreUI.h"
#include "Ball.h"
#include "Paddle.h"
#include "Particle.h"
#include "Constants.h"
#include "HandleSDL.h"
#include "Utility.h"
#include "InputSummary.h"
#include "textures.h"
#include "Init.h"
#include "GameState.h"
#include "Update.h"
#include "Music.h"


struct InputSummary HandleInput(
    struct Paddle paddles[2], 
    float deltaTime, bool screenWrapping
)
{
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {  
        switch (event.type) {
            case SDL_QUIT:
                return (struct InputSummary) { false, false };

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return (struct InputSummary) { false, false };
                }
                else if (event.key.keysym.sym == SDLK_SPACE) {
                    screenWrapping = !screenWrapping;
                    break;
                }

            default:
                break;    
        }
    }

    UpdatePaddle( &paddles[0], deltaTime, 
        keyState[SDL_SCANCODE_S] - keyState[SDL_SCANCODE_W]
    );
    UpdatePaddle( &paddles[1], deltaTime, 
        keyState[SDL_SCANCODE_DOWN] - keyState[SDL_SCANCODE_UP]
    );

    return (struct InputSummary) { true, screenWrapping };
}

void PreGame(struct GameState state, int fromWhat)
{
    float deltaTime;
    float currentTime = SDL_GetTicks();
 
    float startTime = SDL_GetTicks();
    while (startTime + fromWhat * 1000 > SDL_GetTicks())
    {
        deltaTime = (SDL_GetTicks() - currentTime) / 1000;
        currentTime = SDL_GetTicks();
        HandleInput(state.scene.Paddles, deltaTime, false);
        UpdateParticles(state.scene.Particles, deltaTime);
        WindowClear(state.scene.SDL.renderer, state.background);

        DrawParticles(
            state.scene.Particles, 
            state.scene.SDL.renderer, 
            CreateTexture(
                state.scene.SDL, 
                "Image\\definetelyNotAMinecraftSprite.png"
            )
        );
        DrawBalls(state.scene.SDL.renderer, state.scene.Balls);
        DrawPaddles(state.scene.SDL.renderer, state.scene.Paddles);
        //printf("6\n");
        AfficherScore(state.scene, state.score[0], state.score[1]);
        //printf("7\n");
        SDL_RenderPresent(state.scene.SDL.renderer); // update display
    }

    KillParticles(state.scene.Particles);
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
        //if (i == 0) ParticlesBurst(currentScene->Particles, 0);
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

    free(currentScene->obstacles);
    currentScene->obstacles = malloc(
        MAX_OBSTACLE_AMOUNT * sizeof(struct Obstacle)
    );
    currentScene->nbr_obstacles = 0;
}

void DrawScene(struct GameState state)
{
    WindowClear(state.scene.SDL.renderer, state.background);

    DrawParticles(
        state.scene.Particles, 
        state.scene.SDL.renderer, 
        CreateTexture(
            state.scene.SDL, 
            "Image\\definetelyNotAMinecraftSprite.png"
        )
    );

    DrawBalls(state.scene.SDL.renderer, state.scene.Balls);
    DrawPaddles(state.scene.SDL.renderer, state.scene.Paddles);
    DrawObstacles(state.scene);
    AfficherScore(state.scene, state.score[0], state.score[1]);
    SDL_RenderPresent(state.scene.SDL.renderer); // update display
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

    PlaySound(song, state.scene.SDL);

    PreGame(state, 3);

    Update(state);

    CloseSDL(state);

    return 0;
}


// sensitivity
// change ball angle?
// bonuses
// particles
// render score

