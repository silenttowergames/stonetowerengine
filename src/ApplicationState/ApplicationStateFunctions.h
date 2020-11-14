#pragma once

#include "ApplicationState.h"

ApplicationState ApplicationState_Init(int2d resolution);
void ApplicationState_Loop(ApplicationState* app);
void ApplicationState_Free(ApplicationState* app);
