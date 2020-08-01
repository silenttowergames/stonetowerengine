#pragma once

#include "ApplicationState.h"

ApplicationState ApplicationState_Create(
    const char* gameTitle,
    const char* gameVersion,
    const char* graphicsDriver,
    int FPS,
    int sizeX,
    int sizeY,
    int resX,
    int resY,
    void (*flecsInit)(ecs_world_t*),
    void (*flecsScene)(ecs_world_t*)
);
void ApplicationState_Loop(ApplicationState* app);
void ApplicationState_Free(ApplicationState* app);
