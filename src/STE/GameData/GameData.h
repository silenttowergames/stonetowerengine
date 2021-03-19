#pragma once

#include "GameDataAttribute.h"
#include "../vendor/rxi/ini/ini.h"

typedef struct GameData
{
    const char* filename;
    char* filepath;
    int length;
    GameDataAttribute* data;
    ecs_map_t* map;
    ini_t* loadedFile;
} GameData;
