#pragma once

#include <flecs.h>
#include "TiledJSONProperty.h"
#include "../Utilities/float2d.h"

typedef struct TiledJSONObject
{
    int id;
    float2d position;
    const char* name;
    const char* type;
    int layer;
    ecs_map_t* properties;
    TiledJSONProperty* propertiesArray;
    int propertiesCount;
} TiledJSONObject;

#define getProperty(obj, key) (obj == NULL ? NULL : mapGet(obj->properties, key, TiledJSONProperty))
