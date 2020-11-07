#include <stdio.h>
#include <flecs.h>

#include "ApplicationState/ApplicationStateInit.h"
#include "ApplicationState/ApplicationStateFunctions.h"
#include "ECS/FlecsFunctions.h"

int main()
{
    printf("Flecs\n");
    
    app = ApplicationState_Init();
    
    ecs_world_t* world = NULL;
    
    do {
        world = Flecs_Init();
        
        while(ecs_progress(world, 0))
        {
            printf("Frame\n");
        }
    }
    while(0);
    
    return 0;
}
