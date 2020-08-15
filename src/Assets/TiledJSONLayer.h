#pragma once

#include "TiledJSONObject.h"
#include "../Utilities/int2d.h"

typedef struct TiledJSONLayer
{
    const char* type;
    const char* name;
    int id;
    int2d size;
    int* tiles;
    TiledJSONObject* objects;
    int count;
    int realCount;
} TiledJSONLayer;
