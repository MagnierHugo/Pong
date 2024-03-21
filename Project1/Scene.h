#pragma once

#include <stdbool.h>

#include "SDLStruct.h"

struct Scene
{
    struct Ball* Balls;
    struct Paddle* Paddles;
    struct SDL SDL;
    bool ScreenWrappingActive;
};