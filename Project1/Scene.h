#pragma once

#include <stdbool.h>

#include "SDLStruct.h"
#include "scoreUI.h"
#include "obstacle.h"

struct Scene
{
    struct Ball* Balls;
    struct Paddle* Paddles;
    struct SDL SDL;
    struct Particle* Particles;
    struct Score* images;
    struct Obstacle* obstacles;
    int nbr_obstacles;
    bool ScreenWrappingActive;
};