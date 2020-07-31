#include "StoneTower.h"

void initWorld(ecs_world_t* world)
{
    ECS_COMPONENT(world, int);
    ECS_SYSTEM(world, SDLEventsSystem, EcsOnUpdate, int);
    ECS_SYSTEM(world, DrawSystem, EcsOnUpdate, int);
}

void initScene(ecs_world_t* world)
{
    ECS_COMPONENT(world, int);
    ecs_new(world, int);
}

int main(int arcg, char* argv[])
{
    init(
        "OpenGL",
        60,
        1280, 720,
        320, 180,
        initWorld,
        initScene
    );
    
    Shader shader = Shader_Create(&app, "SpriteEffect");
    // TODO: shader compilation pipeline
    
    loop();
    
    Shader_Free(&shader);
    
    quit();
}
