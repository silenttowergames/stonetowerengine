#pragma once

#include <flecs.h>
#include "../Application/ApplicationState.h"

ecs_world_t* Flecs_Init(ApplicationState* app);
ecs_world_t* Flecs_Free(ecs_world_t* world);
