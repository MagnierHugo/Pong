#pragma once

#include <stdbool.h>

#include "Bonus.h"
#include "SDLStruct.h"
#include "scoreUI.h"

struct Scene
{
    struct Ball* Balls;
    struct Paddle* Paddles;
    struct SDL SDL;
    struct Particle* Particles;
    struct Bonus Bonus;
    struct Score* images;
    bool ScreenWrappingActive;
};