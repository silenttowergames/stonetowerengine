#pragma once

#include <flecs.h>
#include "RenderState.h"
#include "../ECS/FlecsFunctions.h"
#include "../Utilities/float2d.h"
#include "../Utilities/int2d.h"
#include "../Logging/Logger.h"

typedef struct ApplicationState
{
    const char* title;
    const char* version;
    FlecsState flecsState;
    RenderState renderState;
    Logger logger;
} ApplicationState;
