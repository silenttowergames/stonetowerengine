#include "TextBoxFactory.h"
#include "../Components/Body.h"
#include "../Components/RenderableFunctions.h"
#include "../Components/RenderOffsetFunctions.h"
#include "../../Assets/Font.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Utilities/colorFunctions.h"

ecs_entity_t TextBoxFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ecs_entity_t e = ecs_new(world, 0);
    
    ecs_set(world, e, Body, bodyEasy(X, Y));
    ecs_set(world, e, Renderable,
        RenderableText(
            "PressStart2P/PressStart2P.ttf",
            8,
            5,
            1,
            1,
            colorU(0, 0, 255, 255),
            0,
            "Retro"
        )
    );
    
    return e;
}
