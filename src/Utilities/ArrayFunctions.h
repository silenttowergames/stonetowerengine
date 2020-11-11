#pragma once

#include <flecs.h>
#include "Array.h"

#define ARRAY_CREATE(var, length, T) var = Array_Init(length, sizeof(T)); var.map = ecs_map_new(T, length)
#define ARRAY_ADD(var, T, value) if(var.length < var.allocated)\
{\
    ((T*)var.data)[var.length] = value;\
    ecs_map_set(var.map, ((T)value).key, &((T*)var.data)[var.length]);\
    var.length++;\
}

Array Array_Init(int length, size_t size);
