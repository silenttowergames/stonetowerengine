#pragma once

#include <flecs.h>
#include "../Utilities/int2d.h"

typedef struct Config
{
    int2d size;
    int2d windowedSize;
    bool fullscreen;
    const char* language;
} Config;
