#pragma once

#include <SDL2/SDL.h>

uint64_t Flecs_Map_Key(const char* key);

#define mapKey(key) Flecs_Map_Key(key)
#define mapSet(map, key, value) ecs_map_set(map, mapKey(key), value)
#define mapGet(map, key, type) ecs_map_get(map, type, mapKey(key))
