#pragma once

#include "Menu.h"
#include "../../Application/ApplicationState.h"

typedef struct MenuItem
{
    ecs_entity_t menu;
    void (*select)(ApplicationState*, ecs_entity_t, Menu*);
    void (*hovering)(ApplicationState*, ecs_entity_t, Menu*);
} MenuItem;

void MenuItem_Select_Test(ApplicationState* app, ecs_entity_t entityID, Menu* menu)
{
    const Renderable* renderable = ecs_get(app->world, entityID, Renderable);
    
    printf("Menu item selected: %s\n", (char*)renderable->data);
}

void MenuItem_Select_Disable(ApplicationState* app, ecs_entity_t entityID, Menu* menu)
{
    menu->active = false;
}

#define menuItemEasy(menuEntityID, itemVarName, itemCountVarName, renderableValue, itemSelectEvent, itemHoveringEvent) \
    itemVarName[itemCountVarName] = ecs_new(world, 0); \
    ecs_set(world, itemVarName[itemCountVarName], Body, { 0, 0, }); \
    ecs_set(world, itemVarName[itemCountVarName], Renderable, renderableValue); \
    ecs_set(world, itemVarName[itemCountVarName], MenuItem, { menuEntityID, itemSelectEvent, itemHoveringEvent, }); \
    itemCountVarName++;
