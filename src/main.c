#include "includes.c"

void initWorld(ecs_world_t* world)
{
    ECS_COMPONENT(world, int);
    ECS_COMPONENT(world, float);
    ECS_SYSTEM(world, Test1System, EcsOnUpdate, int);
    //ECS_SYSTEM(world, Test2System, EcsOnUpdate, float);
    ECS_SYSTEM(world, SDLEventsSystem, EcsOnUpdate, int);
}

void initScene(ecs_world_t* world)
{
    ECS_COMPONENT(world, int);
    ecs_new(world, int);
}

typedef struct TestStruct
{
    int hello;
} TestStruct;

int main(int arcg, char* argv[])
{
    ApplicationState app = ApplicationState_Create(NULL, 60, initWorld, initScene);
    
    ApplicationState_Loop(&app);
    
    ApplicationState_Free(&app);
    
    return 0;
}
