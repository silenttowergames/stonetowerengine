#include "PlayerFactory.h"
#include "../Components/AIPlayer.h"
#include "../Components/Animate.h"
#include "../Components/BasicAABB.h"
#include "../Components/Body.h"
#include "../Components/CameraFollow.h"
#include "../Components/RenderableFunctions.h"
#include "../../Assets/TiledJSONProperty.h"

void PlayerFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ECS_COMPONENT(world, AIPlayer);
	ECS_COMPONENT(world, Animate);
    ECS_COMPONENT(world, BasicAABB);
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, CameraFollow);
    ECS_COMPONENT(world, Renderable);
    
    ecs_entity_t e = ecs_new(world, 0);
    
    // Example of using properties
    TiledJSONProperty* prop = getProperty(object, "modify");
    if(prop != NULL && prop->valueBool)
    {
        X += 32;
    }
    
    ecs_set(world, e, AIPlayer, {
        1.3f,
    });
    ecs_set(world, e, Animate, {
        "protag-walk",
        NULL,
        0,
        0,
        1.0f,
    });
    ecs_set(world, e, BasicAABB, {
        Hitbox_CreateList(1, Hitbox_CreateSquare(8)),
    });
    ecs_set(world, e, Body, {
        { X, Y, },
    });
    //*
    ecs_set(world, e, CameraFollow, {
        { 0, 0, },
    });
    //*/
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
        NULL,
        0,
        0,
    });
}
