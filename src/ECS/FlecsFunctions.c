#include "FlecsFunctions.h"

ecs_world_t* Flecs_Init()
{
    ecs_world_t* world = ecs_init(); // world allocate
    
    ecs_set_target_fps(world, 60);
    
    return world;
}

void Flecs_Free(ecs_world_t* world)
{
    ecs_fini(world); // world free
}
