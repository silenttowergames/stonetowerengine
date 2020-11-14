#pragma once

#include <flecs.h>
#include "FlecsState.h"

FlecsState Flecs_Init();
ecs_world_t* Flecs_Create_World(FlecsState* flecsState);
void Flecs_Free(ecs_world_t* world);
