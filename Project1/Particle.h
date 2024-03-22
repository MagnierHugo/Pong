#pragma once

#include <stdbool.h>
#include <SDL.h>
#include "SDLStruct.h"
#include "Ball.h"
#include "HandleSDL.h"
#include "Constants.h"
#include "Utility.h"

struct Particle {
    int X;
    int Y;

    int DirX;
    int DirY;

    float Size;
    bool Active;
};

void UpdateParticles(struct Particle* particles, float deltaTime);
SDL_Rect ParticleAsRect(struct Particle particle);
void DrawParticles(struct Particle* particles, SDL_Renderer* renderer, SDL_Texture* texture);
void ParticlesBurst(struct Particle* particles, int directionX);
void KillParticles(struct Particle* particles);