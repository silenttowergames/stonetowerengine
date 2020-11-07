#include "FlecsFunctions.h"

ecs_world_t* Flecs_Init()
{
    ecs_world_t* world = ecs_init();
    
    ecs_set_target_fps(world, 1);
    
    return world;
}
