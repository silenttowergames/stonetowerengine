#pragma once

#include <flecs.h>

static void FinalizeScreenSystem_ToMainRT(ApplicationState* app);
static void FinalizeScreenSystem_ToWindow(ApplicationState* app);
static void FinalizeScreenSystem_UI(ApplicationState* app);
void FinalizeScreenSystem(ecs_iter_t* it);
