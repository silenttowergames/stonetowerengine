#include "FlecsFunctions.h"
#include "FlecsState.h"

FlecsState Flecs_Init()
{
    FlecsState flecsState;
    memset(&flecsState, 0, sizeof(flecsState));
    
    ecs_os_set_api_defaults();
    
    flecsState.FPS = 60;
    
    return flecsState;
}

ecs_world_t* Flecs_Create_World(FlecsState* flecsState)
{
    ecs_world_t* world = ecs_init(); // world allocate
    
    ecs_set_target_fps(world, flecsState->FPS);
    
    if(flecsState->worldInit != NULL)
    {
        flecsState->worldInit(world);
    }
    
    return world;
}

void Flecs_Free(ecs_world_t* world)
{
    printf("Freeing the world\n");
    
    if(world == NULL)
    {
        return;
    }
    
    ecs_fini(world); // world free
}
