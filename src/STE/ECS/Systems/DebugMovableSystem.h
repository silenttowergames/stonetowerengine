#pragma once

#include <flecs.h>

static ecs_query_t* DebugMovableSystemQuery = NULL;

void DebugMovableSystem(ecs_iter_t* it);

#define DebugMovableSystem_Init()\
    DebugMovableSystemQuery = ecs_query_new(world, "Renderable, Body");\
    ECS_SYSTEM(world, DebugMovableSystem, EcsOnUpdate, 0);
