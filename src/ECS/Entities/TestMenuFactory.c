#include "TestMenuFactory.h"

#include "../Components/Body.h"
#include "../Components/Menu.h"
#include "../Components/MenuItem.h"
#include "../Components/RenderableFunctions.h"
#include "../../Application/ApplicationStateFunctions.h"

void TestMenuFactory(ecs_world_t* world, float X, float Y, int layer, TiledJSONObject* object)
{
    ctx();
    
    ECS_COMPONENT(world, Body);
    ECS_COMPONENT(world, Menu);
    ECS_COMPONENT(world, MenuItem);
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
            "This Is A Menu!"
        )
    );
    menuEasy(items, currentItem, e, 5, Menu_ItemUpdate_Basic, Menu_MenuUpdate_Basic);
    
    menuItemEasy(
        e,
        items,
        currentItem,
        RenderableText(
            "PressStart2P" "/" "PressStart2P.ttf",
            8,
            5,
            1,
            0,
            colorU(255, 255, 255, 255),
            0,
            "Item 0"
        ),
        MenuItem_Select_Test,
        NULL
    );
    
    menuItemEasy(
        e,
        items,
        currentItem,
        RenderableText(
            "PressStart2P" "/" "PressStart2P.ttf",
            8,
            5,
            1,
            0,
            colorU(255, 255, 255, 255),
            0,
            "Item 1"
        ),
        MenuItem_Select_Test,
        NULL
    );
    
    menuItemEasy(
        e,
        items,
        currentItem,
        RenderableText(
            "PressStart2P" "/" "PressStart2P.ttf",
            8,
            5,
            1,
            0,
            colorU(255, 255, 255, 255),
            0,
            "Item 2"
        ),
        MenuItem_Select_Test,
        NULL
    );
    
    menuItemEasy(
        e,
        items,
        currentItem,
        RenderableText(
            "PressStart2P" "/" "PressStart2P.ttf",
            8,
            5,
            1,
            0,
            colorU(255, 255, 255, 255),
            0,
            "Item 3"
        ),
        MenuItem_Select_Test,
        NULL
    );
    
    menuItemEasy(
        e,
        items,
        currentItem,
        RenderableText(
            "PressStart2P" "/" "PressStart2P.ttf",
            8,
            5,
            1,
            0,
            colorU(255, 255, 255, 255),
            0,
            "Item 4"
        ),
        MenuItem_Select_Test,
        NULL
    );
}
