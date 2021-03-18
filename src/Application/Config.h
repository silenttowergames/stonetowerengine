#pragma once

#include <flecs.h>
#include "../Utilities/int2d.h"

typedef struct Config
{
    int2d size;
    int2d windowedSize;
    bool fullscreen;
    char* language;
    bool vsync;
    bool debug;
    float volumeMaster;
    float volumeSFX;
    float volumeMusic;
} Config;

#define configDefault(c, w, h, lang, _debug) Config c; memset(&c, 0, sizeof(Config)); c.windowedSize.X = w; c.windowedSize.Y = h; c.fullscreen = false; c.language = malloc(sizeof(char) * (strlen(lang) + 1)); strcpy(c.language, lang); c.vsync = false; c.debug = _debug; c.volumeMaster = 1.0f; c.volumeSFX = 0.5f; c.volumeMusic = 0.5f;
