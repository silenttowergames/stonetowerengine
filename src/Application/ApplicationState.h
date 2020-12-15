#pragma once

#include <flecs.h>
#include "Config.h"
#include "../Assets/AssetManager.h"
#include "../Input/InputManager.h"
#include "../ECS/Entities/Factory.h"
#include "../Logging/LoggerFunctions.h"
#include "../Rendering/RenderState.h"
#include "../Scenes/Scene.h"
#include "../includes_vendor.h"

typedef struct ApplicationState
{
    const char* gameTitle;
    const char* gameVersion;
    bool quit;
    int sceneCount;
    bool focused;
    Logger logger;
    const char* graphicsDriver;
    ecs_world_t* world;
    void (*flecsInit)(ecs_world_t*);
    const char* flecsScene;
    int FPS;
    RenderState renderState;
    AssetManager assetManager;
    ecs_map_t* entityFactories;
    Factory* entityFactoriesArray;
    int entityFactoriesLength;
    int entityFactoriesLengthSoFar;
    InputManager inputManager;
    ecs_map_t* sceneFactories;
    Scene* sceneFactoriesArray;
    int sceneFactoriesLength;
    int sceneFactoriesLengthSoFar;
    FONScontext* fons;
    Config config;
    const char* savePath;
    char* savePathConfig;
    mu_Context* mui;
    void (*muiUpdate)(void*);
    Texture muiTexture;
} ApplicationState;
