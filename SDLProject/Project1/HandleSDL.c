#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDLStruct.h"

int ErrorHandling(char* message, bool sdl, SDL_Window* window) {

    printf("%s", message);
    if (sdl) {
        SDL_Quit();
        if (window != NULL) {
            SDL_DestroyWindow(window);
        }
    }
    return -1;
}

struct SDL StartSDL() {

    int exitCode = 0;

    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        exitCode = ErrorHandling("Erreur SDL Init failed\n", false, NULL);
    }

    //creer une fenetre avec SDL
    SDL_Window* window = SDL_CreateWindow(
        "Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        exitCode = ErrorHandling("Erreur creation fenêtre SDL\n", true, NULL);
    }

    //Creer rendu SDL
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == NULL) {
        exitCode = ErrorHandling("Erreur creation rendu SDL\n", true, window);
    }

    return (struct SDL) { window, renderer, exitCode };
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
                return false;
            }
            break;

        case SDL_QUIT:
            return false;
            break;

        default:
            break;
    }

    return true;
}