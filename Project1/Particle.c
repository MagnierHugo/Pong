#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>
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


// direction -1 -> towards left -> called beacause left screen at the right
// | direction 1 -> towards right -> called beacause left screen at the left
// direction 0 -> neutral -> called upon ballSpawn
void ParticlesBurst(struct Particle* particles, int directionX)
{
	for (int i = 0; i < MAX_PARTICLE_AMOUNT; i++)
	{
		struct Particle* particle = &particles[i];
		switch (directionX)
		{
			case -1:
				particle->X = SCREEN_WIDTH;
				particle->Y = RdmInt(0, SCREEN_HEIGHT - INITIAL_PARTICLE_SIZE, false);
				particle->DirX = RdmInt(-MAX_PARTICLE_DIR_X, -MIN_PARTICLE_DIR_X, true);
				break;

			case 1:
				particle->X = 0;
				particle->Y = RdmInt(0, SCREEN_HEIGHT - INITIAL_PARTICLE_SIZE, false);
				particle->DirX = RdmInt(MIN_PARTICLE_DIR_X, MAX_PARTICLE_DIR_X, true);
				break;

			case 0:
				particle->X = SCREEN_WIDTH / 2 - INITIAL_PARTICLE_SIZE / 2;
				particle->Y = SCREEN_HEIGHT / 2 - INITIAL_PARTICLE_SIZE / 2;
				particle->DirX = RdmInt(-MAX_PARTICLE_DIR_X, MAX_PARTICLE_DIR_X, true);
				break;
		}

		particle->DirY = RdmInt(-MAX_PARTICLE_DIR_Y, MAX_PARTICLE_DIR_Y, true);
		particle->Size = INITIAL_PARTICLE_SIZE;
		particle->Active = true;

	}
}

void UpdateParticles(struct Particle* particles, float deltaTime)
{
	for (int i = 0; i < MAX_PARTICLE_AMOUNT; i++)
	{
		struct Particle* currentParticle = &particles[i];
		if (!currentParticle->Active) { continue; }
		currentParticle->X += currentParticle->DirX * deltaTime;
		currentParticle->Y += currentParticle->DirY * deltaTime;
		
		currentParticle->DirX *= PARTICLE_SLOWDOWN_RATE;
		currentParticle->DirY *= PARTICLE_SLOWDOWN_RATE;
		currentParticle->Size -= PARTICLE_DECAY_RATE * deltaTime;
		currentParticle->Active = currentParticle->Size > 0;
	}
}

SDL_Rect ParticleAsRect(struct Particle particle)
{
	return (SDL_Rect)
	{ 
		particle.X ,
		particle.Y,
		particle.Size,
		particle.Size
	};
}

void DrawParticles(struct Particle* particles, SDL_Renderer* renderer, SDL_Texture* texture)
{
	for (int i = 0; i < MAX_PARTICLE_AMOUNT; i++)
	{
		struct Particle currentParticle = particles[i];
		if (!currentParticle.Active) { continue; }
		SDL_Rect particleRect = ParticleAsRect(currentParticle);

		//SDL_SetRenderDrawColor(renderer, curBall.Color.R, curBall.Color.G, curBall.Color.B, curBall.Color.A);
		//SDL_RenderFillRect(renderer, &ballRect);
		SDL_RenderCopy(renderer, texture, NULL, &particleRect);
	}
}

void KillParticles(struct Particle* particles)
{
	for (int i = 0; i < MAX_PARTICLE_AMOUNT; i++)
	{
		particles[i].Active = false;
	}
}