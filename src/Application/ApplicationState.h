#pragma once

#include <flecs.h>
#include "../Logging/LoggerFunctions.h"
#include "../Rendering/RenderState.h"

typedef struct ApplicationState
{
    const char* gameTitle;
    const char* gameVersion;
    int quit;
    int counter;
    int sceneCount;
    bool focused;
    Logger logger;
    const char* graphicsDriver;
    ecs_world_t* world;
    void (*flecsInit)(ecs_world_t*);
    void (*flecsScene)(ecs_world_t*);
    int FPS;
    RenderState renderState;
} ApplicationState;
