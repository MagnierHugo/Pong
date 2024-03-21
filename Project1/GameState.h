#pragma once

#include <SDL.h>

#include "Scene.h"
#include "InputSummary.h"

struct GameState {
	struct Scene scene;
	struct InputSummary gameSettings;

	SDL_Texture* background;

	float deltaTime;
	float currentTime;
	int someoneWon;
	int score[2];
};