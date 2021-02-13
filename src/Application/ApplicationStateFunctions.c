#include <SDL2/SDL.h>
#include "ApplicationStateFunctions.h"
#include "ConfigFunctions.h"
#include "../Assets/AssetManagerFunctions.h"
#include "../Assets/FontStashFNA3DFunctions.h"
#include "../Assets/TiledJSONFunctions.h"
#include "../ECS/FlecsFunctions.h"
#include "../ECS/Systems/ConsoleStateSystem.h"
#include "../ECS/Systems/DrawSystem.h"
#include "../ECS/Systems/SDLEventsSystem.h"
#include "../Input/InputManagerFunctions.h"
#include "../Logging/LoggerFunctions.h"
#include "../Rendering/RenderingFunctions.h"
#include "../Rendering/RenderStateFunctions.h"

void ApplicationState_Create(
    ApplicationState* app,
    const char* gameTitle,
    const char* gameVersion,
    const char* graphicsDriver,
    int FPS,
    Config config,
    int resX,
    int resY,
    void (*flecsInit)(ecs_world_t*),
    const char* flecsScene,
    RenderState_Zoom windowZoomType
)
{
	memset(app, 0, sizeof(ApplicationState));
    
    app->focused = true;
    
    app->gameTitle = gameTitle;
    app->gameVersion = gameVersion;
	
	app->FPS = FPS;
	app->graphicsDriver = graphicsDriver;
	app->logger.filename = "log.txt";
	app->flecsInit = flecsInit;
	app->flecsScene = flecsScene;
    
    app->savePath = SDL_GetPrefPath("Silent Tower Games", app->gameTitle); // ApplicationState.savePath allocate
    
    char* configFilename = "config.ini";
    app->savePathConfig = malloc(sizeof(char) * (strlen(app->savePath) + strlen(configFilename) + 2));
    sprintf(app->savePathConfig, "%s/%s", app->savePath, configFilename);
    
    app->config = config;
    
    app->config = Config_Load(app);
    
    app->assetManager = AssetManager_Create();
	
	Rendering_Init(app);
	
	RenderState_New(app, app->config.windowedSize.X, app->config.windowedSize.Y, resX, resY, windowZoomType);
    
    app->inputManager = InputManager_Create();
    
    ecs_os_set_api_defaults();
    SDL_SetHint(SDL_HINT_GAMECONTROLLER_USE_BUTTON_LABELS, "0");
    
    // TODO: FontStash texture size should be modifiable by the game's code
    app->fons = FontStashFNA3D_Create(app, 1024, 1024, FONS_ZERO_TOPLEFT);
}

void ApplicationState_Loop(ApplicationState* app)
{
    const Uint64 freq = SDL_GetPerformanceFrequency();
    
    int64_t accumulator = 0;
    Uint64 currentTime;
    Uint64 deltaTime = 0;
    Uint64 lastTime = SDL_GetPerformanceCounter();
    
    float fDeltaTime;
    float fFPS;
    float fMeasurements[60];
    float fFPSAverage;
    int frameCounter = 0;
    
    Uint64 unit;
    
    // Below is from the Tyler Glaiel method of mixing 62fps logic with 60fps logic
    // It caused a lot of tearing, and vsync was unusable. I must be doing something wrong
    // So for now, this is commented out
    //const Uint64 FPSreal = app->FPS + (app->FPS / 30.0);
    const Uint64 FPSreal = app->FPS;
    const Uint64 FPSrealMS = freq / FPSreal;
    const Uint64 FPSMS = freq / app->FPS;
    
    while(!app->quit)
    {
        app->world = Flecs_Init(app);
        
        if(app->flecsScene != NULL)
        {
            ((FontStashFNA3D*)app->fons->params.userPtr)->renderable = NULL;
            
            ApplicationState_RunScene(app, app->flecsScene);
            
            app->flecsScene = NULL;
        }
        
        while(!app->quit && app->flecsScene == NULL)
        {
            currentTime = SDL_GetPerformanceCounter();
            deltaTime = currentTime - lastTime;
            accumulator += deltaTime;
            
            while(accumulator > FPSrealMS)
            {
                if(accumulator > FPSrealMS * 8)
                {
                    accumulator = FPSrealMS;
                }
                
                fDeltaTime = (float)accumulator / (float)freq;
                fFPS = 1.0f / fDeltaTime;
                
                memcpy(&fMeasurements[1], &fMeasurements[0], sizeof(float) * 59);
                fMeasurements[0] = fFPS;
                
                if(++frameCounter >= 60)
                {
                    frameCounter = 0;
                    
                    fFPSAverage = 0;
                    for(int i = 0; i < 60; i++)
                    {
                        fFPSAverage += fMeasurements[i];
                    }
                    fFPSAverage /= 60;
                    
                    printf("FPS: %1.5f\n", fFPSAverage);
                }
                
                SDLEventsSystem(app);
                
                if(app->focused)
                {
                    ecs_progress(app->world, fDeltaTime);
                    
                    ConsoleStateSystem(app);
                }
                
                accumulator -= FPSMS;
                
                if(accumulator < 0)
                {
                    accumulator = 0;
                }
            }
            
            lastTime = currentTime;
        }
        
        app->world = Flecs_Free(app->world);
    }
}

void ApplicationState_Free(ApplicationState* app)
{
    ecs_map_free(app->sceneFactories); // ApplicationState.sceneFactories free
    free(app->sceneFactoriesArray); // ApplicationState.sceneFactoriesArray free
    
    ecs_map_free(app->entityFactories); // ApplicationState.entityFactories free
    free(app->entityFactoriesArray); // ApplicationState.entityFactoriesArray free
    
    free(app->savePathConfig); // ApplicationState.savePathConfig free
    
    FontStashFNA3D_Free(app->fons->params.userPtr);
    
    AssetManager_Destroy(app->renderState.device, &app->assetManager);
    RenderState_Free(&app->renderState);
    
    SDL_free(app->savePath); // ApplicationState.savePath free
}

void ApplicationState_InitFactories(ApplicationState* app, int length)
{
    app->entityFactoriesLength = length;
    app->entityFactoriesLengthSoFar = 0;
    app->entityFactories = ecs_map_new(Factory, length);
    app->entityFactoriesArray = malloc(sizeof(Factory) * length);
}

void ApplicationState_AddFactories(ApplicationState* app, int length, ...)
{
    ApplicationState_InitFactories(app, length);
    
    va_list args;
    
    va_start(args, length);
    
    for(int i = 0; i < length; i++)
    {
        ApplicationState_AddFactory(app, va_arg(args, Factory));
    }
    
    va_end(args);
}

void ApplicationState_AddFactory(ApplicationState* app, Factory callable)
{
    app->entityFactoriesArray[app->entityFactoriesLengthSoFar] = callable;
    mapSet(app->entityFactories, callable.key, &app->entityFactoriesArray[app->entityFactoriesLengthSoFar]);
    app->entityFactoriesLengthSoFar++;
}

Factory* ApplicationState_GetFactory(ApplicationState* app, const char* key)
{
    Factory* fac = mapGet(app->entityFactories, key, Factory);
    
    if(fac == NULL)
    {
        printf("FACTORY MISSING: %s\n", key);
    }
    
    assert(fac != NULL);
    
    return fac;
}

void ApplicationState_InitScenes(ApplicationState* app, int length)
{
    app->sceneFactoriesLength = length;
    app->sceneFactories = ecs_map_new(Scene, length); // ApplicationState.sceneFactories allocate
    app->sceneFactoriesArray = malloc(sizeof(Scene) * length); // ApplicationState.sceneFactoriesArray allocate
}

void ApplicationState_AddScenes(ApplicationState* app, int length, ...)
{
    ApplicationState_InitScenes(app, length);
    
    va_list args;
    
    va_start(args, length);
    
    for(int i = 0; i < length; i++)
    {
        ApplicationState_AddScene(app, va_arg(args, Scene));
    }
    
    va_end(args);
}

void ApplicationState_AddScene(ApplicationState* app, Scene callable)
{
    app->sceneFactoriesArray[app->sceneFactoriesLengthSoFar] = callable;
    mapSet(app->sceneFactories, callable.key, &app->sceneFactoriesArray[app->sceneFactoriesLengthSoFar]);
    app->sceneFactoriesLengthSoFar++;
}

Scene* ApplicationState_GetScene(ApplicationState* app, const char* key)
{
    return mapGet(app->sceneFactories, key, Scene);
}

void ApplicationState_RunScene(ApplicationState* app, const char* key)
{
    Scene* _scene = ApplicationState_GetScene(app, key);
    
    if(_scene == NULL)
    {
        return;
    }
    
    if(_scene->tiledMap != NULL)
    {
        TiledJSON* map = *mapGet(app->assetManager.mapTiled, _scene->tiledMap, TiledJSON*);
        
        if(map != NULL)
        {
            TiledJSON_Build(app, map);
        }
    }
    
    if(_scene->callable != NULL)
    {
        _scene->callable(app->world);
    }
}
