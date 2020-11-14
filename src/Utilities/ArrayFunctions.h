#pragma once

#include <flecs.h>
#include "Array.h"

#define ARRAY_CREATE(var, length, T) var = Array_Init(length, sizeof(T)); var.map = ecs_map_new(T, length)
#define ARRAY_ADD(var, T, value) if(var.length < var.allocated){ ((T*)var.data)[var.length] = value; ecs_map_set(var.map, ((T)value).key, &((T*)var.data)[var.length]); var.length++; }
#define ARRAY_GROW(var, _length, T) Array_Grow(&var, _length, sizeof(T)); ecs_map_free(var.map); var.map = ecs_map_new(T, _length); for(int A_G = 0; A_G < var.length; A_G++){ ecs_map_set(var.map, ((T*)var.data)[A_G].key, &((T*)var.data)[A_G]); }
#define ARRAY_ADD_GROW(var, T, value) if(var.length >= var.allocated){ ARRAY_GROW(var, var.allocated * 2, T); } ARRAY_ADD(var, T, value)

Array Array_Init(int length, size_t size);
bool Array_Grow(Array* array, int length, size_t size);
void Array_Free(Array* array);
