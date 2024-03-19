#pragma once

#include <SDL.h>

int ErrorHandling(char* message, bool sdl, SDL_Window* window);

void CloseSDL(SDL_Window* window, SDL_Renderer* renderer);

struct SDL StartSDL();

bool CheckExit(SDL_Event event);