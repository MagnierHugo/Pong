#pragma once

#include <SDL.h>
#include <stdbool.h>

struct Obstacle
{
	SDL_Rect rect;
	SDL_Texture* texture;
	bool isBonus;
};

void SpawnObstacles(struct Scene* scene);
void CollisionBallObstacles(struct Scene* scene, struct Ball* ball);
void DrawObstacles(struct Scene scene);
struct Obstacle* ResetObstacles(int nbrObstacles, struct SDL sdlStruct);