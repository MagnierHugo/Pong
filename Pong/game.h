#pragma once
#include <SDL.h>

struct Game GameSetup(SDL_Window* window, SDL_Renderer* renderer);

void RunGame(SDL_Window* window, SDL_Renderer* renderer);