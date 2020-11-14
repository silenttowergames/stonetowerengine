#include <SDL2/SDL.h>
#include "ApplicationStateFunctions.h"
#include "RenderStateFunctions.h"

ApplicationState ApplicationState_Init(int2d resolution)
{
    ApplicationState app;
    
    app.flecsState = Flecs_Init();
    app.renderState = RenderState_Init(resolution);
    
    return app;
}

void ApplicationState_Loop(ApplicationState* app)
{
    do {
        app->flecsState.world = Flecs_Create_World(&app->flecsState);
        
        while(ecs_progress(app->flecsState.world, 0))
        {
            if(app->flecsState.quit)
            {
                break;
            }
        }
        
        Flecs_Free(app->flecsState.world);
        app->flecsState.world = NULL;
    }
    while(!app->flecsState.quit);
}

void ApplicationState_Free(ApplicationState* app)
{
    RenderState_Free(&app->renderState);
}
