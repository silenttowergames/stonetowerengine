#include "PlayerFactory.h"
#include "../Components/Animate.h"
#include "../Components/Body.h"
#include "../Components/RenderableFunctions.h"

void PlayerFactory(ecs_world_t* world, float X, float Y)
{
    ctx();
    
	ECS_COMPONENT(world, Animate);
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Renderable);
    
    ECS_ENTITY(world, e, Animate, Body, Renderable);
    ecs_set(world, e, Animate, {
        "protag-walk",
        NULL,
        0,
        0,
        1.0f,
    });
    ecs_set(world, e, Body, {
        { X, Y, },
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
}
