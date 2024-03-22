#pragma once

#include <stdbool.h>

#include "SDLStruct.h"
#include "scoreUI.h"

struct Scene
{
    struct Ball* Balls;
    struct Paddle* Paddles;
    struct SDL SDL;
    struct Score images;
    bool ScreenWrappingActive;
};