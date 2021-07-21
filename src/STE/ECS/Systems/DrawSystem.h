#pragma once

#include <flecs.h>

void DrawSystem(ecs_iter_t* it);

#define DrawSystem_Init() \
    ECS_SYSTEM(world, DrawSystem, EcsOnUpdate, Body, Renderable);\
    ECS_SYSTEM(world, FinalizeScreenSystem, EcsOnUpdate, 0);\
    ecs_query_t* sort = ecs_query_init(world, &(ecs_query_desc_t){ .filter.terms = { { ecs_id(Renderable), }, }, });\
    ecs_query_order_by(world, sort, ecs_typeid(Renderable), SortByLayerThenY);
