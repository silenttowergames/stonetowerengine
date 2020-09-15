#include "TextBoxFactory.h"
#include "../Components/Body.h"
#include "../Components/RenderableFunctions.h"
#include "../Components/RenderOffsetFunctions.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Utilities/colorFunctions.h"

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
        NULL,
        { 0, 0, },
        { 0, 0, },
        { 1, 1, },
        false,
        false,
        0,
        (void*)"The quick, brown fox jumps over the lazy dog.",
        Renderable_TextBox_Render,
        layer,
        0.5f,
        0,
        colorU(0, 255, 0, 255),
        RenderOffset_Sine,
        0
    });
}
