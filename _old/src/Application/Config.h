#pragma once

#include <flecs.h>
#include "../Utilities/int2d.h"

typedef struct Config
{
    int2d size;
    bool fullscreen;
    const char* language;
} Config;
