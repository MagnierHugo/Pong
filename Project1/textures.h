#pragma once
#include <SDL.h>

SDL_Texture* CreateTexture(SDL_Window* window, SDL_Renderer* renderer, char* path);
void DestroyTextures(SDL_Texture* texture[]);