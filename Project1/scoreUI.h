#pragma once

#include <SDL.h>

struct Score
{
    SDL_Texture* img1;
    SDL_Texture* img2;
    SDL_Texture* img3;
    SDL_Texture* img4;
    SDL_Texture* img5;
};

struct Score InitScore(struct SDL sdlStruct);
void AfficherScore(struct Scene scene, int scoreGauche, int scoreDroite);