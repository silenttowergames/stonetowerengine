#include "TextBoxFactory.h"
#include "../Components/Body.h"
#include "../Components/RenderableFunctions.h"
#include "../../Application/ApplicationStateFunctions.h"

void TextBoxFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Renderable);
    
    ecs_entity_t e = ecs_new(world, 0);
    
    ecs_set(world, e, Body, {
        { X, Y, },
    });
    ecs_set(world, e, Renderable, {
        getTexture("16x16"),
        { 0, 0, },
        { 0, 0, },
        { 1, 1, },
        false,
        false,
        0,
        NULL,
        Renderable_Sprite_Render,
        layer,
        0.5f,
        0,
        0xFFFFFFFF,
    });
}
