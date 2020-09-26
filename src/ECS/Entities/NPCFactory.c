#include <stdlib.h>
#include "NPCFactory.h"
#include "../Components/Animate.h"
#include "../Components/Body.h"
#include "../Components/RenderableFunctions.h"
#include "../../Application/ApplicationStateFunctions.h"

void NPCFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
	ctx();
	
    ECS_COMPONENT(world, Animate);
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Renderable);
	
	ecs_entity_t f = ecs_new(world, 0);
    
    ecs_set(world, f, Animate, {
        "man-die",
        NULL,
        0,
        0,
        1.0f,
    });
    ecs_set(world, f, Body, {
        { X, Y, },
    });
    ecs_set(world, f, Renderable, {
        getTexture("8x8"),
        { 0, 0, },
        { 0, 0, },
        { 1, 1, },
        false,
        false,
        0,
        NULL,
        Renderable_Sprite_Render,
        layer,
        (rand() % 10) / 10.0f,
        0,
        0xFFFFFFFF,
        NULL,
        0,
        1,
    });
}
