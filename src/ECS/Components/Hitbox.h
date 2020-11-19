#pragma once

#include <flecs.h>
#include "../../Utilities/float2d.h"

typedef struct Hitbox
{
    float2d size;
    float2d offset;
    bool solidBottom;
    bool solidLeft;
    bool solidRight;
    bool solidTop;
    bool active;
} Hitbox;
