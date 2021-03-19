#pragma once

#include "Frame.h"

typedef struct Animation
{
    const char* name;
    int from, to;
    const char* direction;
} Animation;
