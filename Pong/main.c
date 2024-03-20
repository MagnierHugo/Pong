#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pong.h"
#include "game.h"
#include "sdl_handling.h"


int main(int argc, char* argv[]) {
    
    struct SDL sdl = StartSDL();

    SDL_Window* window = sdl.window;
    SDL_Renderer* renderer = sdl.renderer;

    RunGame(window, renderer);

    CloseSDL(window, renderer);

    exit(EXIT_SUCCESS);
}