#pragma once

#include <flecs.h>
#include "Renderable.h"
#include "../../Application/ApplicationState.h"
#include "../../Input/KeyboardStateFunctions.h"
#include "../../Utilities/colorFunctions.h"

typedef struct Menu
{
    ecs_entity_t* items;
    int itemCount;
    int itemSelected;
    // applicationState, menuID, itemID, renderable, itemCount, itemSelected, itemIndex
    void (*itemUpdate)(ApplicationState*, ecs_world_t*, ecs_entity_t, ecs_entity_t, Renderable*, int, int, int);
    // applicationState, itemCount, itemSelected; returns new value of itemSelected
    int (*menuUpdate)(ApplicationState*, ecs_world_t*, int, int);
    bool active;
} Menu;
