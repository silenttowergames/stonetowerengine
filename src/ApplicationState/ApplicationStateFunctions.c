#include "ApplicationStateFunctions.h"

ApplicationState ApplicationState_Init()
{
    ApplicationState app;
    
    app.world = ecs_init();
    
    return app;
}
