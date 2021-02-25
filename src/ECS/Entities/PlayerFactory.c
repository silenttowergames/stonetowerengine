#include "PlayerFactory.h"
#include "../Components/AIPlayer.h"
#include "../Components/Animate.h"
#include "../Components/BasicAABB.h"
#include "../Components/Body.h"
#include "../Components/CameraFollow.h"
#include "../Components/RenderableFunctions.h"
#include "../../Assets/AssetManagerFunctions.h"
#include "../../Assets/TiledJSONObject.h"
#include "../../Assets/TiledJSONProperty.h"
#include "../../Application/ApplicationStateFunctions.h"

void PlayerFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ecs_entity_t e = ecs_new(world, 0);
    
    // Example of using properties
    TiledJSONProperty* prop = getProperty(object, "modify");
    if(prop != NULL && prop->valueBool)
    {
        X += 32;
    }
    
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
    ecs_set(world, e, BasicAABB, BasicAABB_Create(1, Hitbox_CreateSquare(16)));
    ecs_set(world, e, Body, bodyEasy(X, Y));
    ecs_set(world, e, CameraFollow, {
        { 0, 0, },
    });
    ecs_set(world, e, Renderable, RenderableSprite(
        getTexture("16x16"),
        int2dInit(0, 0),
        layer,
        0.5f,
        1,
        0xFFFFFFFF,
        2
    ));
}
