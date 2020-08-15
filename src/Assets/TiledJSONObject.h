#pragma once

#include "../Utilities/float2d.h"

typedef struct TiledJSONObject
{
    int id;
    float2d position;
    const char* name;
    const char* type;
    int layer;
} TiledJSONObject;
