#pragma once

#include <flecs.h>

typedef struct Scene
{
    const char* key;
    const char* tiledMap;
    void (*callable)(ecs_world_t*);
} Scene;
