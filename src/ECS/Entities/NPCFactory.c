#include <stdlib.h>
#include "NPCFactory.h"
#include "../Components/AINPC.h"
#include "../Components/Animate.h"
#include "../Components/BasicAABB.h"
#include "../Components/Body.h"
#include "../Components/RenderableFunctions.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Utilities/colorFunctions.h"

void NPCFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
	ctx();
	
    ECS_COMPONENT(world, AINPC);
    ECS_COMPONENT(world, Animate);
    ECS_COMPONENT(world, BasicAABB);
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Renderable);
	
	ecs_entity_t f = ecs_new(world, 0);
    
    ecs_set(world, f, AINPC, {
        0.25f,
    });
    ecs_set(world, f, Animate, {
        "man-die",
        NULL,
        0,
        0,
        1.0f,
    });
    ecs_set(world, f, BasicAABB, BasicAABB_Create(1, Hitbox_CreateSquare(8)));
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
        colorU(255, 255, 0, 100),//0xFFFFFFFF,
        NULL,
        0,
        0,
    });
}
