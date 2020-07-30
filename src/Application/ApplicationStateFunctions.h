#pragma once

#include "ApplicationState.h"

ApplicationState ApplicationState_Create(const char* graphicsDriver, int FPS, void (*flecsInit)(ecs_world_t*), void (*flecsScene)(ecs_world_t*));
void ApplicationState_Loop(ApplicationState* app);
void ApplicationState_Free(ApplicationState* app);
