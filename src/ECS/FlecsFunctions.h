#pragma once

#include <flecs.h>

ecs_world_t* Flecs_Init();
void Flecs_Free(ecs_world_t* world);
