#pragma once

#include <flecs.h>
#include "../Application/ApplicationState.h"

ecs_world_t* Flecs_Init(ApplicationState* app);
ecs_world_t* Flecs_Free(ecs_world_t* world);

#define mapKey(key) hashlittle(key, strlen(key), 0)
#define mapSet(map, key, value) ecs_map_set(map, mapKey(key), value)
#define mapGet(map, key, type) ecs_map_get(map, type, mapKey(key))
