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
void ApplicationState_AddFactories(ApplicationState* app, int length, ...);
void ApplicationState_AddFactory(ApplicationState* app, Factory callable);
Factory* ApplicationState_GetFactory(ApplicationState* app, const char* key);

#define init(...) ApplicationState app; ApplicationState_Create(&app, __VA_ARGS__); freopen(app.logger.filename, "a", stderr)
#define loop() ApplicationState_Loop(&app)
#define quit() ApplicationState_Free(&app); return 0

#define factories(l, ...) ApplicationState_AddFactories(&app, l, __VA_ARGS__);
#define factory(c) (Factory){ #c, c ## Factory, }
#define factoryRun(app, key, X, Y, layer) Factory* key ## FactoryVarX ## X ## xY ## Y = ApplicationState_GetFactory(app, #key); key ## FactoryVarX ## X ## xY ## Y->callable(app->world, X, Y, layer)

#define ctx() ApplicationState* app = (ApplicationState*)ecs_get_context(world)
#define fctx() ApplicationState* app = (ApplicationState*)ecs_get_context(it->world)
