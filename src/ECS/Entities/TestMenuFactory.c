#include "TestMenuFactory.h"

#include "../Components/Body.h"
#include "../Components/RenderableFunctions.h"
#include "../../Application/ApplicationStateFunctions.h"

void TestMenuFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Renderable);
    
    ecs_entity_t e = ecs_new(world, 0);
    
    ecs_set(world, e, Body, {
        { X, Y, },
    });
    ecs_set(world, e, Renderable,
        RenderableText(
            "Bloodyslime/Bloodyslime.ttf",
            32,
            5,
            1,
            0,
            colorU(255, 0, 0, 255),
            0,
            "SLASHER"
        )
    );
}
