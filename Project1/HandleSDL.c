#include <SDL.h>
//#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "SDLStruct.h"
#include "Constants.h"

int ErrorHandling(char* message, bool sdl, SDL_Window* window) {

    printf("%s\n", message);
    if (sdl) {
        SDL_Quit();
        if (window != NULL) {
            SDL_DestroyWindow(window);
        }
    }
    exit(EXIT_FAILURE);
}

struct SDL StartSDL() {

    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ErrorHandling("Erreur SDL Init failed", false, NULL);
    }

    //creer une fenetre avec SDL
    SDL_Window* window = SDL_CreateWindow(
        "Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        ErrorHandling("Erreur creation fenêtre SDL", true, NULL);
    }

    //Creer rendu SDL
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == NULL) {
        ErrorHandling("Erreur creation rendu SDL", true, window);
    }

    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        ErrorHandling("initialisation du module police SDL", true, window);
    }

    return (struct SDL) { window, renderer };
}

void CloseSDL(SDL_Window* window, SDL_Renderer* renderer) {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool CheckExit(SDL_Event event) {

    // Stop game if the right key is down
    switch (event.type) {

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                return true;
            }
            break;

        case SDL_QUIT:
            return true;
            break;

        default:
            break;
    }

    return false;
}