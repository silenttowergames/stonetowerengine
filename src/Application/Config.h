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
} Config;

#define configDefault(c, w, h, lang) Config c; memset(&c, 0, sizeof(Config)); c.windowedSize.X = w; c.windowedSize.Y = h; c.fullscreen = false; c.language = lang; c.vsync = false;
