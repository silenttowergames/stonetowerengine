#pragma once

#include <flecs.h>
#include "FlecsMapFunctions.h"
#include "../Application/ApplicationState.h"

ecs_world_t* Flecs_Init(ApplicationState* app);
ecs_world_t* Flecs_Free(ecs_world_t* world);

#define fdelta() (1.0f / ((1.0f / app->FPS) / it->delta_time))
