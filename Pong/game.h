#pragma once
#include <SDL.h>

void DrawGameObject(SDL_Renderer* renderer, SDL_Rect* object, struct Color color);

struct Game GameSetup(SDL_Window* window, SDL_Renderer* renderer);

void RunGame(SDL_Window* window, SDL_Renderer* renderer);