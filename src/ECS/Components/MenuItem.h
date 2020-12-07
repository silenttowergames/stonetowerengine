#pragma once

#include "Menu.h"
#include "../../Application/ApplicationState.h"

typedef struct MenuItem
{
    ecs_entity_t menu;
    void (*select)(ApplicationState*, ecs_entity_t);
    void (*hovering)(ApplicationState*, ecs_entity_t);
} MenuItem;

void MenuItem_Select_Test(ApplicationState* app, ecs_entity_t entityID)
{
    ECS_COMPONENT(app->world, Renderable);
    
    bool out;
    Renderable* renderable = ecs_get_mut(app->world, entityID, Renderable, &out);
    
    printf("Menu item selected: %s\n", (char*)renderable->data);
}

#define menuItemEasy(menuEntityID, itemVarName, itemCountVarName, renderableValue, itemSelectEvent, itemHoveringEvent) \
    itemVarName[itemCountVarName] = ecs_new(world, 0); \
    ecs_set(world, itemVarName[itemCountVarName], Body, { 0, 0, }); \
    ecs_set(world, itemVarName[itemCountVarName], Renderable, renderableValue); \
    ecs_set(world, itemVarName[itemCountVarName], MenuItem, { menuEntityID, itemSelectEvent, itemHoveringEvent, }); \
    itemCountVarName++;
