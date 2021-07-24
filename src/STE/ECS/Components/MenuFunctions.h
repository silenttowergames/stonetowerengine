#pragma once

#include "Menu.h"

int Menu_MenuUpdate_Basic(ApplicationState* app, ecs_world_t* world, int itemCount, int itemSelected);

void Menu_ItemUpdate_Basic(ApplicationState* app, ecs_world_t* world, ecs_entity_t menuID, ecs_entity_t itemID, Renderable* renderable, int itemCount, int itemSelected, int itemIndex);

#define menuEasy(itemVarName, itemCountVarName, menuEntityID, count, eventItem, eventMenu, active) \
    int itemCountVarName = 0; \
    ecs_entity_t* itemVarName = malloc(sizeof(ecs_entity_t*) * count); \
    ecs_set(world, menuEntityID, Menu, { itemVarName, count, 0, eventItem, eventMenu, active, })
