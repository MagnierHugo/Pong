#pragma once 

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "SDLStruct.h"
#include "Scene.h"

int ErrorHandling(char* message, bool sdl, SDL_Window* window, SDL_Renderer* renderer);

struct SDL StartSDL();

void CloseSDL(struct Scene scene);

void WindowClear(SDL_Renderer* renderer);
void WindowClear(SDL_Renderer* renderer, SDL_Texture* texture);

