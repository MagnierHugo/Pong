#pragma once
#include <SDL.h>

struct Color { int R, G, B, A; };

struct SDL {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int exitCode;
};

struct MovementVector {
	int x;
	int y;
};

struct GameObject {
	char* id;
	SDL_Rect rect;
	struct Color color;
	struct MovementVector movement;
};

struct Game {
	struct GameObject gameObjects[50];

	int leftPlayerScore;
	int rightPlayerScore;
};