#include "ApplicationStateFunctions.h"
#include "../ECS/FlecsFunctions.h"
#include "../Logging/LoggerFunctions.h"
#include "../Rendering/RenderingFunctions.h"
#include "../Rendering/RenderStateFunctions.h"

ApplicationState ApplicationState_Create(const char* graphicsDriver, int FPS, void (*flecsInit)(ecs_world_t*), void (*flecsScene)(ecs_world_t*))
{
	ApplicationState app;
	memset(&app, 0, sizeof(ApplicationState));
	
	app.FPS = FPS;
	app.graphicsDriver = graphicsDriver;
	app.logger.filename = "log.txt";
	app.flecsInit = flecsInit;
	app.flecsScene = flecsScene;
	
	Rendering_Init(&app);
	
	app.renderState = RenderState_New();
	
	return app;
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
                app->counter = 0;
                
                break;
            }
        }
        
        app->world = Flecs_Free(app->world);
    }
}

void ApplicationState_Free(ApplicationState* app)
{
    //RenderState_Free(app->renderState);
}
