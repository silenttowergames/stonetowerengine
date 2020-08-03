#include "StoneTower.h"

void initWorld(ecs_world_t* world)
{
    ECS_COMPONENT(world, int);
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Renderable);
    // TODO: SDLEventsSystem should call whether or not there are components of any kind
    ECS_SYSTEM(world, SDLEventsSystem, EcsOnUpdate, int);
    ECS_SYSTEM(world, DrawSystem, EcsOnUpdate, int);
    
    ECS_ENTITY(world, EntitySDLEvents, int);
}

void initScene(ecs_world_t* world)
{
    ApplicationState* app = (ApplicationState*)ecs_get_context(world);
    
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Renderable);
    
    ECS_ENTITY(world, e, Body, Renderable);
    ecs_set(world, e, Body, {
        { 0, 0, },
    });
    ecs_set(world, e, Renderable, {
        &app->renderState.texture,
        { 0, 0, },
        { 1, 1, },
        NULL,
        Renderable_Sprite_Render,
    });
    // ecs_set_ptr_w_entity(world, e, FLECS__ERenderable, sizeof(Renderable), &(Renderable){ &app->renderState.texture, { 0, 0, }, { 1, 1, }, ((void *)0), Renderable_Sprite_Render })
}

int main(int arcg, char* argv[])
{
    init(
        "Engine Test",
        "v1.0.0",
        "OpenGL",
        60,
        1280, 720,
        320, 180,
        initWorld,
        initScene
    );
    
    app.renderState.texture = Texture_Load(app.renderState.device, "16x16");
    app.renderState.texture.tilesize.X = 16;
    app.renderState.texture.tilesize.Y = 16;
    
    loop();
    
    quit();
}
