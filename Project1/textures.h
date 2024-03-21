#pragma once
#include <SDL.h>

SDL_Texture* CreateTexture(struct SDL sdlStruct, char* path);
void DestroyTextures(struct GameState state);