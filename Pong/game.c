#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "pong.h"
#include "sdl_handling.h"


struct Game game;

void DrawGameObject(SDL_Renderer* renderer, SDL_Rect* object, struct Color color) {

	SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
	SDL_RenderFillRect(renderer, object);
}

struct Game GameSetup(SDL_Window* window, SDL_Renderer* renderer) {

	int windowWidth;
	int windowHeight;

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	game.leftPlayer = (SDL_Rect){ 50, 100, 20, 50 };

	game.rightPlayer = (SDL_Rect){ 750, 100, 20, 50 };

	game.ball = (SDL_Rect){ windowWidth/2, windowHeight/2, 40, 40 };

	game.playerColor = (struct Color){ 255, 255, 255, 255 };
	game.ballColor = (struct Color){ 255, 255, 255, 255 };

	game.leftPlayerScore = 0;
	game.rightPlayerScore = 0;
	game.playerSpeed = 2;
	game.ballSpeed = 3;

	return game;
}

void RunGame(SDL_Window* window, SDL_Renderer* renderer) {

    SDL_Event event;
    struct Game game = GameSetup(window, renderer);

    bool run;

	do
	{
		// Effacer le rendu et afficher le fond en noir
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//Afficher les différents objets
		DrawGameObject(renderer, &game.leftPlayer, game.playerColor);
		DrawGameObject(renderer, &game.rightPlayer, game.playerColor);
		DrawGameObject(renderer, &game.ball, game.ballColor);

		// Update du rendu
		SDL_RenderPresent(renderer);

		// Check for SDL Event
		if (SDL_PollEvent(&event)) run = CheckExit(event);
		else run = true;

	} while (run);
}