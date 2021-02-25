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

static SDL_Surface* windowIcon = NULL;

static void ApplicationState_SetWindowIcon(ApplicationState* app, char* filename)
{
    int2d size = { 16, 16, };
    int channels;
    
    //unsigned char* pixels = stbi_load(filename, &size.X, &size.Y, &channels, 4);
    
    Uint16 pixels[16*16] = {  // ...or with raw pixel data:
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
        0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
        0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
        0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
        0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
        0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
        0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
        0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
        0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
        0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
        0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
        0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
        0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
        0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
        0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
        0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
        0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
        0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
        0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
        0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
        0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
        0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
        0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
    };
    
    if(windowIcon != NULL)
    {
        SDL_FreeSurface(windowIcon);
    }
    
    windowIcon = SDL_CreateRGBSurfaceFrom(pixels, size.X, size.Y, 16, 16*2, 0xF00, 0x0F0, 0x00F, 0xF000); // windowIcon allocate
    
    SDL_SetWindowIcon(app->renderState.window, windowIcon);
    
    printf("%s\n", filename);
}

void ApplicationState_Create(
    ApplicationState* app,
    const char* gameTitle,
    const char* gameVersion,
    const char* graphicsDriver,
    int FPS,
    Config config,
    int resX,
    int resY,
    int fsW,
    int fsH,
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
    
    printf("%s %s\nStone Tower Engine %s by Silent Tower Games\n", app->gameTitle, app->gameVersion, STE_VERSION);
    
    if(app->config.debug)
    {
        printf("===\nDEBUG MODE ACTIVE\n===\n");
    }
    
    app->assetManager = AssetManager_Create();
	
	Rendering_Init(app);
	
	RenderState_New(app, app->config.windowedSize.X, app->config.windowedSize.Y, resX, resY, windowZoomType);
    
    app->inputManager = InputManager_Create();
    
    ecs_os_set_api_defaults();
    SDL_SetHint(SDL_HINT_GAMECONTROLLER_USE_BUTTON_LABELS, "0");
    
    printf("FontStash texture size: %dx%d\n", fsW, fsH);
    app->fons = FontStashFNA3D_Create(app, fsW, fsH, FONS_ZERO_TOPLEFT);
    
    // Load window icon
    ApplicationState_SetWindowIcon(app, "assets/icon.png");
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
    
    if(windowIcon != NULL)
    {
        SDL_FreeSurface(windowIcon); // windowIcon free
    }
    
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
