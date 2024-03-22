#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Color.h"
#include "HandleSDL.h"
#include "SDLStruct.h"

int RdmInt(int min, int max, bool nonZero)
{
    int rdm;
    do
    {
        rdm = min + rand() % (max - min + 1);
    } while (nonZero && rdm == 0);

    return rdm;
}

struct Color RandomColor()
{
    return (struct Color)
    {
        RdmInt(0, 255, false),
        RdmInt(0, 255, false),
        RdmInt(0, 255, false),
        255
    };
}