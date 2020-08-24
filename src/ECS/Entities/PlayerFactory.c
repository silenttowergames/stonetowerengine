#include "PlayerFactory.h"
#include "../Components/Animate.h"
#include "../Components/Body.h"
#include "../Components/RenderableFunctions.h"

void PlayerFactory(ecs_world_t* world, float X, float Y, int layer)
{
    ctx();
    
    ECS_COMPONENT(world, AIPlayer);
	ECS_COMPONENT(world, Animate);
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Renderable);
    
    ecs_entity_t e = ecs_new(world, 0);
    
    ecs_set(world, e, AIPlayer, {
        1.0f,
    });
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
        0,
        0.5f,
    });
}
