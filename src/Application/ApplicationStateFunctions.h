#pragma once

#include "ApplicationState.h"

void ApplicationState_Create(
    ApplicationState* app,
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

#define init(...) ApplicationState app; ApplicationState_Create(&app, __VA_ARGS__); freopen(app.logger.filename, "a", stderr)
#define loop() ApplicationState_Loop(&app)
#define quit() ApplicationState_Free(&app); return 0
