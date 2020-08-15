#include "ApplicationStateFunctions.h"
#include "../Assets/AssetManagerFunctions.h"
#include "../ECS/FlecsFunctions.h"
#include "../Logging/LoggerFunctions.h"
#include "../Rendering/RenderingFunctions.h"
#include "../Rendering/RenderStateFunctions.h"

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
    
    app->assetManager = AssetManager_Create();
	
	Rendering_Init(app);
	
	RenderState_New(app, sizeX, sizeY, resX, resY);
    
    ecs_os_set_api_defaults();
}

void ApplicationState_Loop(ApplicationState* app)
{
	while(!app->quit)
    {
        app->world = Flecs_Init(app);
        
        if(app->flecsScene != NULL)
        {
            app->flecsScene(app->world);
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
    RenderState_Free(&app->renderState);
}

void ApplicationState_InitFactories(ApplicationState* app, int length)
{
    app->entityFactoriesLength = length;
    app->entityFactoriesLengthSoFar = 0;
    app->entityFactories = ecs_map_new(Factory, length);
    app->entityFactoriesArray = malloc(sizeof(Factory) * length);
}

void ApplicationState_AddFactory(ApplicationState* app, Factory callable)
{
    app->entityFactoriesArray[app->entityFactoriesLengthSoFar] = callable;
    ecs_map_set(app->entityFactories, callable.key, &app->entityFactoriesArray[app->entityFactoriesLengthSoFar]);
    app->entityFactoriesLengthSoFar++;
}

Factory* ApplicationState_GetFactory(ApplicationState* app, const char* key)
{
    return ecs_map_get(app->entityFactories, Factory, key);
}
