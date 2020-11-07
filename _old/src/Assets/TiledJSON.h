#pragma once

#include <flecs.h>
#include "TiledJSONLayer.h"
#include "Texture.h"

typedef struct TiledJSON
{
    const char* key;
    char* filename;
    Texture* texture;
    int2d tilesize;
    int layerCount;
    TiledJSONLayer* layers;
    ecs_map_t* layersMap;
} TiledJSON;
