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

void ApplicationState_InitFactories(ApplicationState* app, int length);
void ApplicationState_AddFactory(ApplicationState* app, Factory callable);
Factory* ApplicationState_GetFactory(ApplicationState* app, const char* key);

#define init(...) ApplicationState app; ApplicationState_Create(&app, __VA_ARGS__); freopen(app.logger.filename, "a", stderr)
#define loop() ApplicationState_Loop(&app)
#define quit() ApplicationState_Free(&app); return 0

#define factoriesInit(l) ApplicationState_InitFactories(&app, l); Factory factoryUse; memset(&factoryUse, 0, sizeof(Factory))
#define factory(c) factoryUse.key = #c; factoryUse.callable = c ## Factory; ApplicationState_AddFactory(&app, factoryUse)
#define factoryRun(app, key, X, Y) Factory* key ## FactoryVar = ApplicationState_GetFactory(app, #key); key ## FactoryVar->callable(app->world, X, Y)

#define ctx() ApplicationState* app = (ApplicationState*)ecs_get_context(world)
