#include "ApplicationStateFunctions.h"
#include "ConfigFunctions.h"
#include "../Assets/AssetManagerFunctions.h"
#include "../Assets/FontStashFNA3DFunctions.h"
#include "../Assets/TiledJSONFunctions.h"
#include "../ECS/FlecsFunctions.h"
#include "../ECS/Systems/DrawSystem.h"
#include "../Logging/LoggerFunctions.h"
#include "../Rendering/RenderingFunctions.h"
#include "../Rendering/RenderStateFunctions.h"
#include "../Input/InputManagerFunctions.h"

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
    
    app->gameTitle = gameTitle;
    app->gameVersion = gameVersion;
	
	app->FPS = FPS;
	app->graphicsDriver = graphicsDriver;
	app->logger.filename = "log.txt";
	app->flecsInit = flecsInit;
	app->flecsScene = flecsScene;
    
    app->savePath = SDL_GetPrefPath("Silent Tower Games", app->gameTitle);
    
    char* configFilename = "config.bin";
    app->savePathConfig = malloc(sizeof(char) * (strlen(app->savePath) + strlen(configFilename) + 2));
    sprintf(app->savePathConfig, "%s/%s", app->savePath, configFilename);
    
    app->config = config;
    
    app->config = Config_Load(app);
    
    app->assetManager = AssetManager_Create();
	
	Rendering_Init(app);
	
	RenderState_New(app, app->config.size.X, app->config.size.Y, resX, resY, windowZoomType);
    
    app->inputManager = InputManager_Create();
    
    ecs_os_set_api_defaults();
    
    app->fons = FontStashFNA3D_Create(app, 80, 80, FONS_ZERO_TOPLEFT);
    int fontP2P = fonsAddFont(app->fons, "sans", "assets/fonts/PressStart2P/PressStart2P.ttf");
    fonsSetFont(app->fons, fontP2P);
}

void ApplicationState_Loop(ApplicationState* app)
{
	while(!app->quit)
    {
        app->world = Flecs_Init(app);
        
        if(app->flecsScene != NULL)
        {
            ApplicationState_RunScene(app, app->flecsScene);
            
            app->flecsScene = NULL;
        }
        
        while(ecs_progress(app->world, 0))
        {
            // FIXME: Is it an issue that it plays two frames when you change scenes?
            if(app->quit || app->flecsScene != NULL)
            {
                break;
            }
        }
        
        app->world = Flecs_Free(app->world);
    }
}

void ApplicationState_Free(ApplicationState* app)
{
    AssetManager_Destroy(app->renderState.device, &app->assetManager);
    RenderState_Free(&app->renderState);
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
    return mapGet(app->entityFactories, key, Factory);
}

void ApplicationState_InitScenes(ApplicationState* app, int length)
{
    app->sceneFactoriesLength = length;
    app->sceneFactories = ecs_map_new(Scene, length);
    app->sceneFactoriesArray = malloc(sizeof(Scene) * length);
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
        TiledJSON* map = mapGet(app->assetManager.mapTiled, _scene->tiledMap, TiledJSON);
        
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
