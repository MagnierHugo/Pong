#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "Utility.h"
#include "textures.h"
#include "SDLStruct.h"
#include "Scene.h"
#include "Ball.h"
#include "Paddle.h"


void SpawnObstacles(struct Scene* scene)
{
	if (RdmInt(0, 200, false) == 66 && 
		scene->nbr_obstacles < MAX_OBSTACLE_AMOUNT)
	{
		bool isBonus = RdmInt(0, 1, false) == 1;
		scene->obstacles[scene->nbr_obstacles] = (struct Obstacle){
			(SDL_Rect) {
				(SCREEN_WIDTH - 50) / 2,
				RdmInt(0, SCREEN_HEIGHT - 50, false),
				50, 50
			},
			CreateTexture(
				scene->SDL,
				isBonus ? "Image\\Hugo.png" : "Image\\tristan.png"
			),
			isBonus
		};

		scene->nbr_obstacles++;
	}
}

void DrawObstacles(struct Scene scene)
{
	struct Obstacle* obstacles = scene.obstacles;
	for (int obstacleIndex = 0; obstacleIndex < scene.nbr_obstacles; 
		obstacleIndex++)
	{
		struct Obstacle currentObstacle = obstacles[obstacleIndex];
		SDL_RenderCopy(scene.SDL.renderer, currentObstacle.texture, 
			NULL, &currentObstacle.rect);
	}
}

struct Obstacle* ResetObstacles(int nbrObstacles, struct SDL sdlStruct) {
	struct Obstacle* obstacles = malloc(
		MAX_OBSTACLE_AMOUNT * sizeof(struct Obstacle)
	);

	for (int obstacleIndex = 0; obstacleIndex < nbrObstacles; obstacleIndex++)
	{
		bool isBonus = RdmInt(0, 1, false) == 1;
		obstacles[obstacleIndex] = (struct Obstacle){
		(SDL_Rect) {
			(SCREEN_WIDTH - 50) / 2,
			RdmInt(0, SCREEN_HEIGHT - 50, false),
			50, 50
		},
		CreateTexture(
				sdlStruct,
				isBonus ? "Image\\Hugo.png" : "Image\\tristan.png"
		), 
			isBonus
		};
	}

	return obstacles;
}

void CollisionBallObstacles(struct Scene* scene, struct Ball* ball)
{
	struct Obstacle* obstacles = scene->obstacles;

	SDL_Rect ballRect = BallAsRect(*ball);

	for (int obstacleIndex = 0;
		obstacleIndex < scene->nbr_obstacles; obstacleIndex++)
	{
		struct Obstacle currentObstacle = obstacles[obstacleIndex];

		if (SDL_HasIntersection(&ballRect, &currentObstacle.rect))
		{
			if (currentObstacle.isBonus) {
				currentObstacle = (struct Obstacle ) { NULL, NULL, NULL };
				scene->Paddles[ball->DirX > 0 ? 0 : 1].Height += PADDLE_EXTENDING_AMOUNT;
				scene->obstacles[obstacleIndex] = currentObstacle;
			}
			else
			{
				ball -> DirX *= -1;
				scene->nbr_obstacles--;
				scene->obstacles = ResetObstacles(scene->nbr_obstacles, scene->SDL);
			}
		}
	}
}