#pragma once

#include "GameDataAttribute.h"

typedef struct GameData
{
    const char* filename;
    GameDataAttribute* data;
    ecs_map_t* map;
} GameData;
