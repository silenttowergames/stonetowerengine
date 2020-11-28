#pragma once

#include <flecs.h>

typedef struct Menu
{
    ecs_entity_t* items;
    int itemCount;
} Menu;
