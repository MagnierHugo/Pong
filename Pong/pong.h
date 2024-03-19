#pragma once
#include <SDL.h>

struct Color { int R, G, B, A; };

struct SDL {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int exitCode;
};

struct Game {
	SDL_Rect leftPlayer;
	SDL_Rect rightPlayer;
	SDL_Rect ball;

	struct Color playerColor;
	struct Color ballColor;

	int leftPlayerScore;
	int rightPlayerScore;

	int playerSpeed;
	int ballSpeed;
};