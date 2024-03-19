#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "pong.h"
#include "game.h"
#include "sdl_handling.h"


int main(int argc, char* argv[]) {
    
    struct SDL sdl = StartSDL();

    if (sdl.exitCode == -1) return -1;

    SDL_Window* window = sdl.window;
    SDL_Renderer* renderer = sdl.renderer;

    RunGame(window, renderer);

    CloseSDL(window, renderer);

    return 0;
}