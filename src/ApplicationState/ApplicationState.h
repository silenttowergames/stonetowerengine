#pragma once

#include <flecs.h>
#include "../Utilities/float2d.h"
#include "../Utilities/int2d.h"

typedef struct ApplicationState
{
    const char* title;
    const char* version;
    ecs_world_t* world;
    bool quit;
    int2d resolution;
} ApplicationState;
