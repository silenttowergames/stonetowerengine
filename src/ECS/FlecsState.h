#pragma once

#include <flecs.h>

typedef struct FlecsState
{
    ecs_world_t* world;
    int FPS;
    void (*worldInit)(ecs_world_t*);
    bool quit;
} FlecsState;
