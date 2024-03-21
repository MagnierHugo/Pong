#include <stdlib.h>
#include <stdbool.h>

#include "Color.h"

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