#pragma once 

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDLStruct.h"

int ErrorHandling(char* message, bool sdl, SDL_Window* window, SDL_Renderer* renderer);

struct SDL StartSDL();

void CloseSDL(SDL_Window* window, SDL_Renderer* renderer);

bool CheckExit(SDL_Event event);

