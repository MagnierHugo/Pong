#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL.h>

#include "pong.h"
#include "sdl_handling.h"
#include "movement.h"


struct Game game;

static void DrawGameObjects(SDL_Renderer* renderer, struct GameObject* gameObjects) {

	for (int objectIndex = 0; objectIndex < sizeof(gameObjects); objectIndex++)
	{
		// Initialisation of the draw color based on the object's color
		SDL_SetRenderDrawColor(
			renderer, 
			gameObjects[objectIndex].color.R, 
			gameObjects[objectIndex].color.G, 
			gameObjects[objectIndex].color.B, 
			gameObjects[objectIndex].color.A
		);

		// Prepare the object to be rendered
		SDL_RenderFillRect(renderer, &gameObjects[objectIndex].rect);
	}
	
}

static int HandleInputs(SDL_Event event, struct PressedKey pressedKeys[10], int nbrKeys) {

	if (event.type == SDL_KEYDOWN) {
		for (int keyIndex = 0; keyIndex < nbrKeys; keyIndex++)
		{
			if (event.key.keysym.sym == pressedKeys[keyIndex].keyCode)
			{
				printf("Key already existed");
				pressedKeys[keyIndex].isPressed = true;
				return nbrKeys;
			}
		}
		pressedKeys[nbrKeys] = (struct PressedKey){
			event.key.keysym.sym,
			true
		};
		return ++nbrKeys;
	}
	else if (event.type == SDL_KEYUP) {

		for (int keyIndex = 0; keyIndex < nbrKeys; keyIndex++)
		{
			if (event.key.keysym.sym == pressedKeys[keyIndex].keyCode)
			{
				pressedKeys[keyIndex].isPressed = false;
				return nbrKeys;
			}
		}
	}
	return nbrKeys;
}

static void ObjectsMovement(struct Game game) {

	for (int objectIndex = 0; objectIndex < sizeof(game.gameObjects); objectIndex++)
	{
		if (strcmp(game.gameObjects[objectIndex].id, "Player")) {
			PlayerEntityMovement(game.gameObjects[objectIndex], game.pressedKeys, game.nbrKeys);
		}
	}
}

struct Game GameSetup(SDL_Window* window, SDL_Renderer* renderer) {

	const int WINDOW_WIDTH;
	const int WINDOW_HEIGTH;
	SDL_GetWindowSize(window, WINDOW_WIDTH, WINDOW_HEIGTH);

	game.gameObjects[0] = (struct GameObject){
		"Player", "LeftPlayer",
		(SDL_Rect){ 50, 100, 20, 50 },
		(struct Color){ 255, 255, 255, 255 },
		(struct MovementVector){ 0, 10 }
	};
	game.gameObjects[1] = (struct GameObject){
		"Player", "RightPlayer",
		(SDL_Rect){ 750, 100, 20, 50 },
		(struct Color){ 255, 255, 255, 255 },
		(struct MovementVector){ 0, 10 }
	};
	game.gameObjects[2] = (struct GameObject){
		"Ball", "Ball1",
		(SDL_Rect){ WINDOW_WIDTH/2, WINDOW_HEIGTH/2, 40, 40 },
		(struct Color){ 255, 255, 255, 255 },
		(struct MovementVector){ 10, 10 }
	};

	game.nbrKeys = 0;

	game.leftPlayerScore = 0;
	game.rightPlayerScore = 0;
	return game;
}

void RunGame(SDL_Window* window, SDL_Renderer* renderer) {

    SDL_Event event;
    struct Game game = GameSetup(window, renderer);

    bool run = true;

	while (run)
	{
		// Effacer le rendu
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//Afficher les différents objets
		DrawGameObjects(renderer, game.gameObjects);

		// Update du rendu
		SDL_RenderPresent(renderer);

		// Check for SDL Event
		while (SDL_PollEvent(&event) != 0)
		{
			if (!CheckExit(event)) { run = false; break; }
			game.nbrKeys = HandleInputs(event, game.pressedKeys, game.nbrKeys);
			if (game.nbrKeys == 10) game.nbrKeys = 0;
			ObjectsMovement(game);
		}
	}
}