#include "includes.c"

int main(int arcg, char* argv[])
{
    ecs_world_t* world = ecs_init(); // flecs.world.create
    
    ECS_SYSTEM(world, SystemPrintHelloWorld, EcsOnUpdate);
    
    ecs_set_target_fps(world, 60);
    
    while(ecs_progress(world, 0))
    {
        // Post-frame?
    }
    
    return ecs_fini(world); // flecs.world.free
}
