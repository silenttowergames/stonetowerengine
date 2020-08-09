#include "StoneTower.h"

void initWorld(ecs_world_t* world)
{
    ECS_COMPONENT(world, int);
    ECS_COMPONENT(world, Animate);
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Renderable);
    ECS_SYSTEM(world, SDLEventsSystem, EcsOnUpdate, 0);
    ECS_SYSTEM(world, AnimateSystem, EcsOnUpdate, Animate, Renderable);
    ECS_SYSTEM(world, DrawSystem, EcsOnUpdate, Body, Renderable);
}

void initScene(ecs_world_t* world)
{
    ApplicationState* app = (ApplicationState*)ecs_get_context(world);
    
    ECS_COMPONENT(world, Animate);
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Renderable);
    
    ECS_ENTITY(world, e, Animate, Body, Renderable);
    ecs_set(world, e, Animate, {
        "protag-walk",
        NULL,
        0,
        0,
    });
    ecs_set(world, e, Body, {
        { 0, 0, },
    });
    ecs_set(world, e, Renderable, {
        ecs_map_get(app->assetManager.mapTexture, Texture, "16x16"),
        { 0, 0, },
        { 0, 0, },
        { 1, 1, },
        false,
        false,
        0,
        NULL,
        Renderable_Sprite_Render,
    });
    
    ECS_ENTITY(world, f, Animate, Body, Renderable);
    ecs_set(world, f, Animate, {
        "man-die",
        NULL,
        0,
        0,
    });
    ecs_set(world, f, Body, {
        { 64, 64, },
    });
    ecs_set(world, f, Renderable, {
        ecs_map_get(app->assetManager.mapTexture, Texture, "8x8"),
        { 0, 0, },
        { 0, 0, },
        { 1, 1, },
        false,
        false,
        0,
        NULL,
        Renderable_Sprite_Render,
    });
    //
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
    
    textures(
        2,
        Texture_Create(app.renderState.device, "16x16", 16, 16, 0, 0, 0, 0),
        Texture_Create(app.renderState.device, "8x8", 8, 8, 0, 0, 0, 0)
    );
    
    loop();
    
    quit();
}
