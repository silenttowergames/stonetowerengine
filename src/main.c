#include "StoneTower.h"

#include <stdio.h>
#include <flecs.h>

#include "ApplicationState/ApplicationStateInit.h"
#include "ApplicationState/ApplicationStateFunctions.h"
#include "ECS/FlecsFunctions.h"
#include "Utilities/ArrayFunctions.h"

int testSystemCounter = 0;
void TestSystem(ecs_iter_t* it)
{
    printf("%1.10f\n", it->delta_time);
    
    if(++testSystemCounter >= 60)
    {
        app.flecsState.quit = true;
    }
}

void worldInit(ecs_world_t* world)
{
    ECS_SYSTEM(world, TestSystem, EcsOnUpdate, 0);
}

int main()
{
    printf("Flecs\n");
    
    app = ApplicationState_Init((int2d){ 320, 180, });
    app.flecsState.quit = true;
    app.flecsState.worldInit = worldInit;
    
    ApplicationState_Loop(&app);
    
    ApplicationState_Free(&app);
    
    return 0;
}
