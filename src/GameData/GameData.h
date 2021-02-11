#pragma once

#include "GameDataAttribute.h"

typedef struct GameData
{
    const char* filename;
    char* filepath;
    int length;
    GameDataAttribute* data;
    ecs_map_t* map;
} GameData;
