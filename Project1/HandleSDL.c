#include <SDL.h>
//#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "SDLStruct.h"
#include "Scene.h"
#include "Constants.h"

int ErrorHandling(char* message, bool sdl, SDL_Window* window, SDL_Renderer* renderer) {

    printf("%s\n", message);
    if (sdl) {
        if (window != NULL) {
            if (renderer != NULL) {
                SDL_DestroyRenderer(renderer);
            }
            SDL_DestroyWindow(window);
        }
        SDL_Quit();
    }
    exit(EXIT_FAILURE);
}

struct SDL StartSDL()
{

    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ErrorHandling("Erreur SDL Init failed", false, NULL, NULL);
    }

    srand(time(NULL));
    //creer une fenetre avec SDL
    SDL_Window* window = SDL_CreateWindow(
        rand() % 2 == 0 ? "Ping" : "Pong",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        ErrorHandling("Erreur creation fenêtre SDL", true, NULL, NULL);
    }

    //Creer rendu SDL
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == NULL) {
        ErrorHandling("Erreur creation rendu SDL", true, window, NULL);
    }

    // Initialize SDL_ttf
    /*if (TTF_Init() < 0) {
        exitCode = ErrorHandling("initialisation du module police SDL\n", true, window);
    }*/

    // TTF_Font* font = TTF_OpenFont("arial.ttf", 28);
    //if (font == NULL) {
    //    exitCode = ErrorHandling("Failed to load font! SDL_ttf Error: %s\n", true, window);
    //}

    return (struct SDL) { window, renderer };
}

void CloseSDL(struct Scene scene)
{

    SDL_DestroyRenderer(scene.SDL.renderer);
    SDL_DestroyWindow(scene.SDL.window);
    SDL_Quit();
}

void WindowClear(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // more of a fill
    SDL_RenderClear(renderer); // more of a fill
    SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
}