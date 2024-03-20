#pragma once
#include <SDL.h>
#include <stdbool.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGTH = 600;

struct Color { int R, G, B, A; };

struct SDL {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

struct MovementVector {
	int x;
	int y;
};

struct GameObject {
	char* id;
	char* name;
	SDL_Rect rect;
	struct Color color;
	struct MovementVector movement;
};

struct PressedKey {
	SDL_Keycode keyCode;
	bool isPressed;
};

struct Game {
	struct GameObject gameObjects[50];

	int leftPlayerScore;
	int rightPlayerScore;

	struct PressedKey pressedKeys[10];
	int nbrKeys;
};