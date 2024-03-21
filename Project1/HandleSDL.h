#pragma once 

#include <SDL.h>

int ErrorHandling(char* message, struct SDL sdlStruct);

struct SDL StartSDL();

void CloseSDL(struct GameState state);

void WindowClear(SDL_Renderer* renderer, SDL_Texture* texture);

