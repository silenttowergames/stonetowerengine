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
        "Engine Test",
        "v1.0.0",
        "Metal",
        60,
        1280, 720,
        320, 180,
        initWorld,
        initScene
    );
    
    app.renderState.texture = Texture_NewBlank(app.renderState.device, 64, 64, 4, false);
    
    loop();
    
    quit();
}
