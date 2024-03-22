#include <SDL.h>
#include <SDL_mixer.h>
//#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "SDLStruct.h"
#include "Scene.h"
#include "Constants.h"
#include "textures.h"
#include "GameState.h"
#include "Utility.h"


int ErrorHandling(char* message, struct SDL sdlStruct) 
{
    printf("%s\n", message);
    if (&sdlStruct != &(struct SDL) { NULL, NULL }) {

        if (sdlStruct.window != NULL) {
            if (sdlStruct.renderer != NULL) {
                SDL_DestroyRenderer(sdlStruct.renderer);
            }
            SDL_DestroyWindow(sdlStruct.window);
        }
        Mix_CloseAudio();
        SDL_Quit();
    }
    exit(EXIT_FAILURE);
}

void InitSDL(struct SDL sdlStruct)
{
    // Initialisation SDL Video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ErrorHandling("Erreur SDL Init failed", sdlStruct);
    }

    // Initialisation SDL Audio
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        ErrorHandling("Erreur initialisation de SDL Audio", sdlStruct);
    }

    // Open Audio Channels
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, NUMBER_OF_CHANNELS, 2048) < 0)
    {
        ErrorHandling("Erreur initialisation de SDL Mixer", sdlStruct);
    }

    Mix_Volume(0, 7);
}

struct SDL StartSDL()
{
    struct SDL sdlStruct = { NULL, NULL };

    InitSDL(sdlStruct);

    srand(time(NULL));
    //creer une fenetre avec SDL
    sdlStruct.window = SDL_CreateWindow(
        rand() % 2 == 0 ? "Ping" : "Pong",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    if (sdlStruct.window == NULL) {
        ErrorHandling("Erreur creation fenêtre SDL", sdlStruct);
    }

    //Creer rendu SDL
    sdlStruct.renderer = SDL_CreateRenderer(
        sdlStruct.window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (sdlStruct.renderer == NULL) {
        ErrorHandling("Erreur creation rendu SDL", sdlStruct);
    }

    return sdlStruct;
}

void CloseSDL(struct GameState state)
{
    DestroyTextures(state);
    SDL_DestroyRenderer(state.scene.SDL.renderer);
    SDL_DestroyWindow(state.scene.SDL.window);
    SDL_Quit();
}

void WindowClear(SDL_Renderer* renderer, SDL_Texture* background)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // more of a fill
    SDL_RenderClear(renderer); // more of a fill
    SDL_RenderCopy(
        renderer, background, NULL,
        &(SDL_Rect){ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }
    );
}