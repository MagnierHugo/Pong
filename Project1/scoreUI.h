#pragma once

#include <SDL.h>

struct Score
{
	SDL_Texture* texture;
};

void AfficherScore(struct Scene scene, int scoreGauche, int scoreDroite);