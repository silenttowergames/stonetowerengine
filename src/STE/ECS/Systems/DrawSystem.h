#pragma once

#include <flecs.h>

void DrawSystem(ecs_iter_t* it);

#define DrawSystem_Init() \
    ECS_SYSTEM(world, DrawSystem, EcsOnUpdate, Body, Renderable);\
    ECS_SYSTEM(world, FinalizeScreenSystem, EcsOnUpdate, 0);\
    const EcsQuery* sort = ecs_get(world, DrawSystem, EcsQuery);\
    ecs_query_order_by(world, sort->query, ecs_entity(Renderable), SortByLayerThenY);
