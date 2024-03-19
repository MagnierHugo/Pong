#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "pong.h"
#include "sdl_handling.h"


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

struct Game GameSetup(SDL_Window* window, SDL_Renderer* renderer) {

	int windowWidth;
	int windowHeight;

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	/*game.leftPlayer = (SDL_Rect){ 50, 100, 20, 50 };

	game.rightPlayer = (SDL_Rect){ 750, 100, 20, 50 };

	game.ball = (SDL_Rect){ windowWidth/2, windowHeight/2, 40, 40 };

	game.playerColor = (struct Color){ 255, 255, 255, 255 };
	game.ballColor = (struct Color){ 255, 255, 255, 255 };

	game.leftPlayerScore = 0;
	game.rightPlayerScore = 0;
	game.playerSpeed = 2;
	game.ballSpeed = { 10, 10 };*/

	game.gameObjects[0] = (struct GameObject){
		"LeftPlayer",
		(SDL_Rect){ 50, 100, 20, 50 },
		(struct Color){ 255, 255, 255, 255 },
		(struct MovementVector){ 0, 10 }
	};
	game.gameObjects[1] = (struct GameObject){
		"RightPlayer",
		(SDL_Rect){ 750, 100, 20, 50 },
		(struct Color){ 255, 255, 255, 255 },
		(struct MovementVector){ 0, 10 }
	};
	game.gameObjects[2] = (struct GameObject){
		"Ball",
		(SDL_Rect){ windowWidth/2, windowHeight/2, 40, 40 },
		(struct Color){ 255, 255, 255, 255 },
		(struct MovementVector){ 10, 10 }
	};

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
		if (SDL_PollEvent(&event)) run = CheckExit(event);
	}
}